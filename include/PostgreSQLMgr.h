#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <pqxx/pqxx>
#include "const.h"

struct UserInfo {
	std::string name;
	std::string pwd;
	int uid;
	std::string email;
};

class SqlConnection {
public:
	SqlConnection(pqxx::connection* con, int64_t lasttime) :_con(con), _last_oper_time(lasttime) {}
	std::unique_ptr<pqxx::connection> _con;
	int64_t _last_oper_time;
};

class SQLPool {
public:
	SQLPool(const std::string& conn_info, int poolSize) : conn_info_(conn_info), poolSize_(poolSize), b_stop_(false) {
		try {
			for (int i = 0; i < poolSize_; ++i) {
				auto conn = new pqxx::connection(conn_info_);
				if (!conn->is_open()) {
					throw std::runtime_error("无法打开 PostgreSQL 连接");
				}

				// 获取当前时间戳
				auto currentTime = std::chrono::system_clock::now().time_since_epoch();
				// 将时间戳转换为秒
				long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();
				pool_.push(std::make_unique<SqlConnection>(conn, timestamp));
			}

			_check_thread = std::thread([this]() {
				while (!b_stop_) {
					checkConnection();
					std::this_thread::sleep_for(std::chrono::seconds(60));
				}
			});

			_check_thread.detach();
		}
		catch (const std::exception& e) {
			// 处理异常
			std::cout << "PostgreSql pool init failed, error is " << e.what() << std::endl;
		}
	}

	// 心跳机制
	void checkConnection() {
		std::lock_guard<std::mutex> guard(mutex_);
		int poolsize = pool_.size();
		// 获取当前时间戳
		auto currentTime = std::chrono::system_clock::now().time_since_epoch();
		// 将时间戳转换为秒
		long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();

		// 循环检测连接上次修改时间，大于10秒更新连接
		for (int i = 0; i < poolsize; i++) {
			auto conn = std::move(pool_.front());
			pool_.pop();
			Defer defer([this, &conn]() {
				pool_.push(std::move(conn));
			});

			if (timestamp - conn->_last_oper_time < 10) {
				continue;
			}

			try {
				pqxx::work tx{ *(conn->_con) };
				pqxx::result r = tx.exec("SELECT 1");
				tx.commit();
				conn->_last_oper_time = timestamp;
				//std::cout << "execute timer alive query , cur is " << timestamp << std::endl;
			}
			catch (const pqxx::sql_error& e) {
				std::cout << "Error keeping connection alive: " << e.what() << std::endl;
				std::cout << "数据库状态: " << e.sqlstate() << std::endl;
			}
		}
	}

	std::unique_ptr<SqlConnection> getConnection() {
		std::unique_lock<std::mutex> lock(mutex_);

		cond_.wait(lock, [this] {
			if (b_stop_) {
				return true;
			}
			return !pool_.empty(); 
		});

		if (b_stop_) {
			return nullptr;
		}

		std::unique_ptr<SqlConnection> conn(std::move(pool_.front()));
		pool_.pop();
		return conn;
	}

	void returnConnection(std::unique_ptr<SqlConnection> conn) {
		std::unique_lock<std::mutex> lock(mutex_);
		if (b_stop_) {
			return;
		}
		pool_.push(std::move(conn));
		cond_.notify_one();
	}

	void Close() {
		b_stop_ = true;
		cond_.notify_all();
	}

	~SQLPool() {
		std::unique_lock<std::mutex> lock(mutex_);
		while (!pool_.empty()) {
			pool_.pop();
		}
	}

private:
	std::string conn_info_;
	int poolSize_;
	std::queue<std::unique_ptr<SqlConnection>> pool_;
	std::mutex mutex_;
	std::condition_variable cond_;
	std::atomic<bool> b_stop_;
	std::thread _check_thread;
};

class PostgreSQLMgr {
public:
	PostgreSQLMgr();
	~PostgreSQLMgr();

	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	int RegUserTransaction(const std::string& name, const std::string& email, const std::string& pwd, const std::string& icon);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePwd(const std::string& name, const std::string& newpwd);
	bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
	bool TestProcedure(const std::string& email, int& uid, std::string& name);

private:
	std::unique_ptr<SQLPool> pool_;
};