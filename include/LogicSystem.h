#pragma once

#include <functional>
#include <map>
#include <nlohmann/json.hpp>
#include "Singleton.h"
#include "StatusGrpcClient.h"
#include "const.h"

class HttpConnection;

typedef std::function<void(std::shared_ptr<HttpConnection>)>HttpHandler; //重定义 封装一个接收httpconnection返回void的函数 为httphandler

class LogicSystem : public Singleton<LogicSystem> {
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem() {
	
	}

	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
	bool HandlePost(std::string path, std::shared_ptr<HttpConnection> con);
	void RegGet(std::string, HttpHandler handler);
	void RegPost(std::string url, HttpHandler handler);

private:
	LogicSystem();
	std::map<std::string, HttpHandler> _post_handlers;
	std::map<std::string, HttpHandler> _get_handlers;
};