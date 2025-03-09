#include "CServer.h"
#include <iostream>
#include "HttpConnection.h"
#include "AsioIOServicePool.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {
	 //引用类型的初始化，socket绑定ioc
}

 //监听连接
void CServer::Start() {
	 //可能在未来某个时刻（或跨线程）执行回调函数。如果回调捕获的是 this（裸指针），而在回调执行前，其它线程的对象已经被析构，那么回调中的 this 就会成为悬空指针，导致未定义行为
	 //异步 I/O 操作（如 async_accept）意味着操作系统或底层库将操作排入事件队列，由 I/O 服务（例如 Boost.Asio 的 io_context）在未来某个时刻处理。这个延迟不可控，也就是说，在事件处理之前，程序的其它部分可能会修改或释放与该操作相关的对象
	auto self = shared_from_this(); //不能用this裸指针
	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);

	_acceptor.async_accept(new_con->GetSocket(), [self, new_con](beast::error_code ec) {
		try {
			//出错放弃连接，监听新连接
			if (ec) {
				self->Start();
				return;
			}

			//处理新连接，新建HttpConnection类管理
			new_con->Start();
			self->Start();
		}
		catch (std::exception& exp) {
			std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
		}
	});
}
