#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include "const.h"
#include "ConfigMgr.h"
#include "RedisMgr.h"
#include "SQLMgr.h"
#include "AsioIOServicePool.h"
#include "StatusServiceImpl.h"

void RunServer() {
	auto& cfg = ConfigMgr::Inst();

	std::string server_address(cfg["StatusServer"]["Host"] + ":" + cfg["StatusServer"]["Port"]);
	StatusServiceImpl service;

	grpc::ServerBuilder builder;
	// �����˿ں���ӷ���
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	// ����������gRPC������
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

	// ����Boost.Asio��io_context
	boost::asio::io_context io_context;
	// ����signal_set���ڲ���SIGINT
	boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

	// �����첽�ȴ�SIGINT�ź�
	signals.async_wait([&server, &io_context](const boost::system::error_code& error, int signal_number) {
		if (!error) {
			std::cout << "Shutting down server..." << std::endl;
			server->Shutdown(); // ���ŵعرշ�����
			io_context.stop(); // ֹͣio_context
		}
		});

	// �ڵ������߳�������io_context
	std::thread([&io_context]() { io_context.run(); }).detach();

	// �ȴ��������ر�
	server->Wait();

}

int main(int argc, char** argv) {
	try {
		RunServer();
		RedisMgr::GetInstance()->Close();
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		RedisMgr::GetInstance()->Close();
		return EXIT_FAILURE;
	}

	return 0;
}
