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
		pqxx::result res = tx.exec_params("SELECT reg_user($1, $2, $3)", name, pwd, email); // reg_user�Ƿ���������PostgreSQL����
		tx.commit();

		// ������
		if (!res.empty()) {
			int result = res[0][0].as<int>();
			std::cout << "���ݿ�ע����Ϊ: " << result << std::endl;
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

		// ���û�в�ѯ����¼���򷵻� false
		if (res.empty()) {
			return false;
		}

		// �����������ͨ��Ӧ��ֻ��һ����¼��
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
			std::cout << "��ѯ������Ϊ��" << std::endl;
			return false; // û���ҵ�ƥ����û�
		}

		std::string origin_pwd = res[0]["user_password"].as<std::string>();
		if (pwd != origin_pwd) {
			return false; // ���벻ƥ��
		}

		std::cout << "��ѯ������: " << origin_pwd << std::endl;

		// ����û���Ϣ
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

//bool MysqlDao::AddFriendApply(const int& from, const int& to)
//{
//	auto con = pool_->getConnection();
//	if (con == nullptr) {
//		return false;
//	}
//
//	Defer defer([this, &con]() {
//		pool_->returnConnection(std::move(con));
//		});
//
//	try {
//		// ׼��SQL���
//		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("INSERT INTO friend_apply (from_uid, to_uid) values (?,?) "
//			"ON DUPLICATE KEY UPDATE from_uid = from_uid, to_uid = to_uid"));
//		pstmt->setInt(1, from); // from id
//		pstmt->setInt(2, to);
//		// ִ�и���
//		int rowAffected = pstmt->executeUpdate();
//		if (rowAffected < 0) {
//			return false;
//		}
//		return true;
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "SQLException: " << e.what();
//		std::cerr << " (MySQL error code: " << e.getErrorCode();
//		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//		return false;
//	}
//
//
//	return true;
//}
//
//bool MysqlDao::AuthFriendApply(const int& from, const int& to) {
//	auto con = pool_->getConnection();
//	if (con == nullptr) {
//		return false;
//	}
//
//	Defer defer([this, &con]() {
//		pool_->returnConnection(std::move(con));
//		});
//
//	try {
//		// ׼��SQL���
//		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("UPDATE friend_apply SET status = 1 "
//			"WHERE from_uid = ? AND to_uid = ?"));
//		//������������ʱfrom����֤ʱto
//		pstmt->setInt(1, to); // from id
//		pstmt->setInt(2, from);
//		// ִ�и���
//		int rowAffected = pstmt->executeUpdate();
//		if (rowAffected < 0) {
//			return false;
//		}
//		return true;
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "SQLException: " << e.what();
//		std::cerr << " (MySQL error code: " << e.getErrorCode();
//		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//		return false;
//	}
//
//
//	return true;
//}
//
//bool MysqlDao::AddFriend(const int& from, const int& to, std::string back_name) {
//	auto con = pool_->getConnection();
//	if (con == nullptr) {
//		return false;
//	}
//
//	Defer defer([this, &con]() {
//		pool_->returnConnection(std::move(con));
//		});
//
//	try {
//
//		//��ʼ����
//		con->_con->setAutoCommit(false);
//
//		// ׼����һ��SQL���, ������֤����������
//		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
//			"VALUES (?, ?, ?) "
//		));
//		//������������ʱfrom����֤ʱto
//		pstmt->setInt(1, from); // from id
//		pstmt->setInt(2, to);
//		pstmt->setString(3, back_name);
//		// ִ�и���
//		int rowAffected = pstmt->executeUpdate();
//		if (rowAffected < 0) {
//			con->_con->rollback();
//			return false;
//		}
//
//		//׼���ڶ���SQL��䣬�������뷽��������
//		std::unique_ptr<sql::PreparedStatement> pstmt2(con->_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
//			"VALUES (?, ?, ?) "
//		));
//		//������������ʱfrom����֤ʱto
//		pstmt2->setInt(1, to); // from id
//		pstmt2->setInt(2, from);
//		pstmt2->setString(3, "");
//		// ִ�и���
//		int rowAffected2 = pstmt2->executeUpdate();
//		if (rowAffected2 < 0) {
//			con->_con->rollback();
//			return false;
//		}
//
//		// �ύ����
//		con->_con->commit();
//		std::cout << "addfriend insert friends success" << std::endl;
//
//		return true;
//	}
//	catch (sql::SQLException& e) {
//		// ����������󣬻ع�����
//		if (con) {
//			con->_con->rollback();
//		}
//		std::cerr << "SQLException: " << e.what();
//		std::cerr << " (MySQL error code: " << e.getErrorCode();
//		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//		return false;
//	}
//
//
//	return true;
//}
//
//std::shared_ptr<UserInfo> MysqlDao::GetUser(int uid)
//{
//	auto con = pool_->getConnection();
//	if (con == nullptr) {
//		return nullptr;
//	}
//
//	Defer defer([this, &con]() {
//		pool_->returnConnection(std::move(con));
//		});
//
//	try {
//		// ׼��SQL���
//		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE uid = ?"));
//		pstmt->setInt(1, uid); // ��uid�滻Ϊ��Ҫ��ѯ��uid
//
//		// ִ�в�ѯ
//		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
//		std::shared_ptr<UserInfo> user_ptr = nullptr;
//		// ���������
//		while (res->next()) {
//			user_ptr.reset(new UserInfo);
//			user_ptr->pwd = res->getString("pwd");
//			user_ptr->email = res->getString("email");
//			user_ptr->name = res->getString("name");
//			user_ptr->nick = res->getString("nick");
//			user_ptr->desc = res->getString("desc");
//			user_ptr->sex = res->getInt("sex");
//			user_ptr->icon = res->getString("icon");
//			user_ptr->uid = uid;
//			break;
//		}
//		return user_ptr;
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "SQLException: " << e.what();
//		std::cerr << " (MySQL error code: " << e.getErrorCode();
//		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//		return nullptr;
//	}
//}
//
//std::shared_ptr<UserInfo> MysqlDao::GetUser(std::string name)
//{
//	auto con = pool_->getConnection();
//	if (con == nullptr) {
//		return nullptr;
//	}
//
//	Defer defer([this, &con]() {
//		pool_->returnConnection(std::move(con));
//		});
//
//	try {
//		// ׼��SQL���
//		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE name = ?"));
//		pstmt->setString(1, name); // ��uid�滻Ϊ��Ҫ��ѯ��uid
//
//		// ִ�в�ѯ
//		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
//		std::shared_ptr<UserInfo> user_ptr = nullptr;
//		// ���������
//		while (res->next()) {
//			user_ptr.reset(new UserInfo);
//			user_ptr->pwd = res->getString("pwd");
//			user_ptr->email = res->getString("email");
//			user_ptr->name = res->getString("name");
//			user_ptr->nick = res->getString("nick");
//			user_ptr->desc = res->getString("desc");
//			user_ptr->sex = res->getInt("sex");
//			user_ptr->uid = res->getInt("uid");
//			break;
//		}
//		return user_ptr;
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "SQLException: " << e.what();
//		std::cerr << " (MySQL error code: " << e.getErrorCode();
//		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//		return nullptr;
//	}
//}
//
//
//bool MysqlDao::GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit) {
//	auto con = pool_->getConnection();
//	if (con == nullptr) {
//		return false;
//	}
//
//	Defer defer([this, &con]() {
//		pool_->returnConnection(std::move(con));
//		});
//
//
//	try {
//		// ׼��SQL���, ������ʼid���������������б�
//		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("select apply.from_uid, apply.status, user.name, "
//			"user.nick, user.sex from friend_apply as apply join user on apply.from_uid = user.uid where apply.to_uid = ? "
//			"and apply.id > ? order by apply.id ASC LIMIT ? "));
//
//		pstmt->setInt(1, touid); // ��uid�滻Ϊ��Ҫ��ѯ��uid
//		pstmt->setInt(2, begin); // ��ʼid
//		pstmt->setInt(3, limit); //ƫ����
//		// ִ�в�ѯ
//		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
//		// ���������
//		while (res->next()) {
//			auto name = res->getString("name");
//			auto uid = res->getInt("from_uid");
//			auto status = res->getInt("status");
//			auto nick = res->getString("nick");
//			auto sex = res->getInt("sex");
//			auto apply_ptr = std::make_shared<ApplyInfo>(uid, name, "", "", nick, sex, status);
//			applyList.push_back(apply_ptr);
//		}
//		return true;
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "SQLException: " << e.what();
//		std::cerr << " (MySQL error code: " << e.getErrorCode();
//		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//		return false;
//	}
//}
//
//bool MysqlDao::GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo> >& user_info_list) {
//
//	auto con = pool_->getConnection();
//	if (con == nullptr) {
//		return false;
//	}
//
//	Defer defer([this, &con]() {
//		pool_->returnConnection(std::move(con));
//		});
//
//
//	try {
//		// ׼��SQL���, ������ʼid���������������б�
//		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("select * from friend where self_id = ? "));
//
//		pstmt->setInt(1, self_id); // ��uid�滻Ϊ��Ҫ��ѯ��uid
//
//		// ִ�в�ѯ
//		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
//		// ���������
//		while (res->next()) {
//			auto friend_id = res->getInt("friend_id");
//			auto back = res->getString("back");
//			//��һ�β�ѯfriend_id��Ӧ����Ϣ
//			auto user_info = GetUser(friend_id);
//			if (user_info == nullptr) {
//				continue;
//			}
//
//			user_info->back = user_info->name;
//			user_info_list.push_back(user_info);
//		}
//		return true;
//	}
//	catch (sql::SQLException& e) {
//		std::cerr << "SQLException: " << e.what();
//		std::cerr << " (MySQL error code: " << e.getErrorCode();
//		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//		return false;
//	}
//
//	return true;
//}
