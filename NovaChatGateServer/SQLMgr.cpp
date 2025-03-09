#include "SQLMgr.h"

SQLMgr::~SQLMgr() {

}

int SQLMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	return _psql.RegUser(name, email, pwd);
}

bool SQLMgr::CheckEmail(const std::string& name, const std::string& email) {
	return _psql.CheckEmail(name, email);
}

bool SQLMgr::UpdatePwd(const std::string& name, const std::string& pwd) {
	return _psql.UpdatePwd(name, pwd);
}

SQLMgr::SQLMgr() {
}

bool SQLMgr::CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo) {
	return _psql.CheckPwd(email, pwd, userInfo);
}

bool SQLMgr::TestProcedure(const std::string& email, int& uid, std::string& name) {
	return _psql.TestProcedure(email, uid, name);
}
