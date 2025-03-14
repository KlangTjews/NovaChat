#pragma once

#include <memory>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
	friend class LogicSystem;
public:
	HttpConnection(boost::asio::io_context& ioc);

	void Start();

	void PreParseGetParam(); //����key��value

	tcp::socket& GetSocket() {
		return _socket;
	}

private:
	void HandleReq(); //��������
	void WriteResponse(); //Ӧ��
	void CheckDeadline(); //��ʱ���

	tcp::socket _socket;
	beast::flat_buffer _buffer{ 8192 }; //���ջ�����
	http::request<http::dynamic_body> _request;
	http::response<http::dynamic_body> _response;
	net::steady_timer deadline_{ //�ײ��¼�ѭ����ʱ��
		_socket.get_executor(), std::chrono::seconds(60) //��socket�����������ù���ʱ��
	};

	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};