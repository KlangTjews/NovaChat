#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifyGrpcClient.h"
#include "RedisMgr.h"
#include "SQLMgr.h"

LogicSystem::LogicSystem() {
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) { //λ表达式封装进HttpHandler
		beast::ostream(connection->_response.body()) << "receive get_test req";
		int i = 0;
		for (auto& elem : connection->_get_params) {
			i++;
			beast::ostream(connection->_response.body()) << "param" << i << "key is" << elem.first;
			beast::ostream(connection->_response.body()) << ", " << "value is" << elem.second << std::endl;
		}
	});

	//RegPost("/test_procedure", [](std::shared_ptr<HttpConnection> connection) {
	//	auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
	//	std::cout << "receive body is " << body_str << std::endl;
	//	connection->_response.set(http::field::content_type, "text/json");
	//	nlohmann::json root;
	//	nlohmann::json src_root;

	//	// 解析 JSON
	//	try {
	//		src_root = nlohmann::json::parse(body_str);
	//	}
	//	catch (const nlohmann::json::parse_error& e) {
	//		std::cout << "Failed to parse JSON data: " << e.what() << std::endl;
	//		root["error"] = ErrorCodes::Error_Json;
	//		std::string jsonstr = root.dump(); // 序列化 JSON
	//		beast::ostream(connection->_response.body()) << jsonstr;
	//		return true;
	//	}

	//	if (!src_root.contains("email") || !src_root["email"].is_string()) {
	//		std::cout << "Failed to parse JSON data!" << std::endl;
	//		root["error"] = ErrorCodes::Error_Json;
	//		std::string jsonstr = root.dump();
	//		beast::ostream(connection->_response.body()) << jsonstr;
	//		return true;
	//	}

	//	auto email = src_root["email"];
	//	int uid = 0;
	//	std::string name = "";
	//	SQLMgr::GetInstance()->TestProcedure(email, uid, name);
	//	std::cout << "email is " << email << std::endl;
	//	root["error"] = ErrorCodes::Success;
	//	root["email"] = src_root["email"];
	//	root["name"] = name;
	//	root["uid"] = uid;
	//	std::string jsonstr = root.dump();
	//	beast::ostream(connection->_response.body()) << jsonstr;
	//	return true;
	//});

	RegPost("/get_verifycode", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");

		nlohmann::json root;
		nlohmann::json src_root;
		// 解析 JSON
		try {
			src_root = nlohmann::json::parse(body_str);
		}
		catch (const nlohmann::json::parse_error& e) {
			std::cout << "Failed to parse JSON data: " << e.what() << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.dump(); // 序列化 JSON
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//是否包含email
		if (!src_root.contains("email") || !src_root["email"].is_string()) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].get<std::string>();
		GetVerifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVerifyCode(email);
		std::cout << "email is " << email << std::endl;
		root["error"] = rsp.error();
		root["email"] = email;
		std::string jsonstr = root.dump();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	});

	//注册用户逻辑
	RegPost("/user_register", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		nlohmann::json root;
		nlohmann::json src_root;
		try {
			src_root = nlohmann::json::parse(body_str);
		}
		catch (const nlohmann::json::parse_error& e) {
			std::cout << "Failed to parse JSON data: " << e.what() << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.dump(); // 序列化 JSON
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].get<std::string>();
		auto name = src_root["user"].get<std::string>();
		auto pwd = src_root["password"].get<std::string>();
		auto confirm = src_root["confirm"].get<std::string>();

		if (pwd != confirm) {
			std::cout << "password err " << std::endl;
			root["error"] = ErrorCodes::PasswdErr;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//先查找redis中email对应的验证码是否合理
		std::string verify_code;
		bool b_get_verify = RedisMgr::GetInstance()->Get(CODEPREFIX + email, verify_code);
		if (!b_get_verify) {
			std::cout << " get verify code expired" << std::endl;
			root["error"] = ErrorCodes::VerifyExpired;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (verify_code != src_root["verifycode"].get<std::string>()) {
			std::cout << " verify code error" << std::endl;
			root["error"] = ErrorCodes::VerifyCodeErr;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//查找数据库判断用户是否存在
		int uid = SQLMgr::GetInstance()->RegUser(name, email, pwd);
		if (uid == 0 || uid == -1) {
			std::cout << " user or email exist" << std::endl;
			root["error"] = ErrorCodes::UserExist;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		root["error"] = 0;
		root["uid"] = uid;
		root["email"] = email;
		root["user"] = name;
		root["password"] = pwd;
		root["confirm"] = confirm;
		root["verifycode"] = src_root["verifycode"];
		std::string jsonstr = root.dump();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	});

	//重置回调逻辑
	RegPost("/reset_pwd", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");

		nlohmann::json root;
		nlohmann::json src_root;
		try {
			src_root = nlohmann::json::parse(body_str);
		}
		catch (const nlohmann::json::parse_error& e) {
			std::cout << "Failed to parse JSON data: " << e.what() << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.dump(); // 序列化 JSON
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].get<std::string>();
		auto name = src_root["user"].get<std::string>();
		auto pwd = src_root["password"].get<std::string>();

		//先查找redis中email对应的验证码是否合理
		std::string verify_code;
		bool b_get_verify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].get<std::string>(), verify_code);
		if (!b_get_verify) {
			std::cout << " get verify code expired" << std::endl;
			root["error"] = ErrorCodes::VerifyExpired;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (verify_code != src_root["verifycode"].get<std::string>()) {
			std::cout << " verify code error" << std::endl;
			root["error"] = ErrorCodes::VerifyCodeErr;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		//查询数据库判断用户名和邮箱是否匹配
		bool email_valid = SQLMgr::GetInstance()->CheckEmail(name, email);
		if (!email_valid) {
			std::cout << " user email not match" << std::endl;
			root["error"] = ErrorCodes::EmailNotMatch;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//更新密码为最新密码
		bool b_up = SQLMgr::GetInstance()->UpdatePwd(name, pwd);
		if (!b_up) {
			std::cout << " update pwd failed" << std::endl;
			root["error"] = ErrorCodes::PasswdUpFailed;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		std::cout << "succeed to update password" << pwd << std::endl;
		root["error"] = 0;
		root["email"] = email;
		root["user"] = name;
		root["password"] = pwd;
		root["verifycode"] = src_root["verifycode"].get<std::string>();
		std::string jsonstr = root.dump();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	});

	//用户登录逻辑
	RegPost("/user_login", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");

		nlohmann::json root;
		nlohmann::json src_root;
		try {
			src_root = nlohmann::json::parse(body_str);
		}
		catch (const nlohmann::json::parse_error& e) {
			std::cout << "Failed to parse JSON data: " << e.what() << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.dump(); // 序列化 JSON
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].get<std::string>();
		auto pwd = src_root["password"].get<std::string>();
		UserInfo userInfo;
		//查询数据库判断用户名和密码是否匹配
		bool pwd_valid = SQLMgr::GetInstance()->CheckPwd(email, pwd, userInfo);
		if (!pwd_valid) {
			std::cout << " user pwd not match" << std::endl;
			root["error"] = ErrorCodes::PasswdInvalid;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//查询StatusServer找到合适的连接
		auto reply = StatusGrpcClient::GetInstance()->GetChatServer(userInfo.uid);
		if (reply.error()) {
			std::cout << " grpc get chat server failed, error is " << reply.error() << std::endl;
			root["error"] = ErrorCodes::RPCFailed;
			std::string jsonstr = root.dump();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		std::cout << "succeed to load userinfo uid is " << userInfo.uid << std::endl;
		root["error"] = 0;
		root["email"] = email;
		root["uid"] = userInfo.uid;
		root["token"] = reply.token();
		root["host"] = reply.host();
		root["port"] = reply.port();
		std::string jsonstr = root.dump();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	});
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> conn) {
	if (_get_handlers.find(path) == _get_handlers.end()) {
		return false;
	}

	_get_handlers[path](conn);
	return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> con) {
	if (_post_handlers.find(path) == _post_handlers.end()) {
		return false;
	}

	_post_handlers[path](con);
	return true;
}

void LogicSystem::RegGet(std::string url, HttpHandler handler) {
	_get_handlers.insert(make_pair(url, handler));
}

void LogicSystem::RegPost(std::string url, HttpHandler handler) {
	_post_handlers.insert(make_pair(url, handler));
}