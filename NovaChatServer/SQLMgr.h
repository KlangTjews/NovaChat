#pragma once

#include <string>
#include "Singleton.h"
#include "PostgreSQLMgr.h"
#include "data.h"

class SQLMgr : public Singleton<SQLMgr> {
	friend class Singleton<SQLMgr>;
public:
	~SQLMgr();

	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePwd(const std::string& name, const std::string& email);
	bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);

private:
	SQLMgr();
	PostgreSQLMgr _psql;
};