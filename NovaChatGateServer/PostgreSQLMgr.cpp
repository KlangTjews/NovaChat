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
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (PostgreSQL SQLState: " << e.sqlstate() << ")" << std::endl;
		return -1;
	}
}

int PostgreSQLMgr::RegUserTransaction(const std::string& name, const std::string& email, const std::string& pwd, const std::string& icon) {
	return 1;
}

bool PostgreSQLMgr::CheckEmail(const std::string& name, const std::string& email) {
	return 1;

}

bool PostgreSQLMgr::UpdatePwd(const std::string& name, const std::string& newpwd) {
	return 1;
}

bool PostgreSQLMgr::CheckPwd(const std::string& name, const std::string& pwd, UserInfo& userInfo) {
	return 1;
}

bool PostgreSQLMgr::TestProcedure(const std::string& email, int& uid, std::string& name) {
	return 1;
}