#include "PostgreSQLMgr.h"
#include "ConfigMgr.h"

PostgreSQLMgr::PostgreSQLMgr() {
	auto& cfg = ConfigMgr::Inst();
	const auto& host = cfg["PostgreSQL"]["Host"];
	const auto& port = cfg["PostgreSQL"]["Port"];
	const auto& pwd = cfg["PostgreSQL"]["Password"];
	const auto& dbname = cfg["PostgreSQL"]["Databasename"];
	const auto& user = cfg["PostgreSQL"]["User"];

	std::string databaseConnectionString = "dbname = " + dbname + " user = " + user + " password = " + pwd + " host = " + host + " port = " + port;
	pool_.reset(new SQLPool(databaseConnectionString, 5));
}

PostgreSQLMgr::~PostgreSQLMgr() {
	pool_->Close();
}

int PostgreSQLMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			return false;
		}

		pqxx::work tx{*(con->_con)};
		pqxx::result res = tx.exec_params("SELECT reg_user($1, $2, $3)", name, pwd, email); // reg_user是返回整数的PostgreSQL函数
		tx.commit();

		// 处理结果
		if (!res.empty()) {
			int result = res[0][0].as<int>();
			std::cout << "数据库注册结果为: " << result << std::endl;
			pool_->returnConnection(std::move(con));
			return result;
		}

		pool_->returnConnection(std::move(con));
		return -1;
	}
	catch (const pqxx::sql_error& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "RegUser SQLException: " << e.what();
		std::cerr << " (PostgreSQL SQLState: " << e.sqlstate() << ")" << std::endl;
		return -1;
	}
}

bool PostgreSQLMgr::CheckEmail(const std::string& name, const std::string& email) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			return false;
		}

		pqxx::work tx{ *(con->_con) };
		std::string query = "SELECT user_email FROM \"user\" WHERE user_name = " + tx.quote(name);
		pqxx::result res = tx.exec(query);
		tx.commit();
		pool_->returnConnection(std::move(con));

		// 如果没有查询到记录，则返回 false
		if (res.empty()) {
			return false;
		}

		// 遍历结果集（通常应该只有一条记录）
		for (const auto& row : res) {
			std::string dbEmail = row["user_email"].as<std::string>();
			std::cout << "Check Email: " << dbEmail << std::endl;
			if (email != dbEmail) {
				return false;
			}
			return true;
		}
		return false;
	}
	catch (const pqxx::sql_error& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "CheckEmail SQLException: " << e.what();
		std::cerr << " (PostgreSQL SQLState: " << e.sqlstate() << ")" << std::endl;
		return -1;
	}
}

bool PostgreSQLMgr::UpdatePwd(const std::string& name, const std::string& newpwd) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			return false;
		}

		pqxx::work tx{ *(con->_con) };
		std::string query = "UPDATE \"user\" SET user_password = $1 WHERE user_name = $2";
		pqxx::result res = tx.exec_params(query, newpwd, name);
		tx.commit();
		pool_->returnConnection(std::move(con));

		std::cout << "Updated rows: " << res.affected_rows() << std::endl;
		return true;
	}
	catch (const pqxx::sql_error& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "RegUser SQLException: " << e.what();
		std::cerr << " (PostgreSQL SQLState: " << e.sqlstate() << ")" << std::endl;
		return -1;
	}
}

bool PostgreSQLMgr::CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		pqxx::work tx{ *(con->_con) };
		std::string query = "SELECT * FROM \"user\" WHERE user_email = $1";
		pqxx::result res = tx.exec_params(query, email);
		tx.commit();

		if (res.empty()) {
			std::cout << "查询到密码为空" << std::endl;
			return false; // 没有找到匹配的用户
		}

		std::string origin_pwd = res[0]["user_password"].as<std::string>();
		if (pwd != origin_pwd) {
			return false; // 密码不匹配
		}

		std::cout << "查询到密码: " << origin_pwd << std::endl;

		// 填充用户信息
		userInfo.uid = res[0]["uid"].as<int>();
		userInfo.name = res[0]["user_name"].as<std::string>();
		userInfo.email = res[0]["user_email"].as<std::string>();
		userInfo.pwd = origin_pwd;

		return true;
	}
	catch (const pqxx::sql_error& e) {
		std::cerr << "CheckPwd SQLException: " << e.what();
		std::cerr << " (PostgreSQL SQLState: " << e.sqlstate() << ")" << std::endl;
		return -1;
	}
}