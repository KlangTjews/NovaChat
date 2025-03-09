#include "CServer.h"
#include <iostream>
#include "HttpConnection.h"
#include "AsioIOServicePool.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {
	 //�������͵ĳ�ʼ����socket��ioc
}

 //��������
void CServer::Start() {
	 //������δ��ĳ��ʱ�̣�����̣߳�ִ�лص�����������ص�������� this����ָ�룩�����ڻص�ִ��ǰ�������̵߳Ķ����Ѿ�����������ô�ص��е� this �ͻ��Ϊ����ָ�룬����δ������Ϊ
	 //�첽 I/O �������� async_accept����ζ�Ų���ϵͳ��ײ�⽫���������¼����У��� I/O �������� Boost.Asio �� io_context����δ��ĳ��ʱ�̴�������ӳٲ��ɿأ�Ҳ����˵�����¼�����֮ǰ��������������ֿ��ܻ��޸Ļ��ͷ���ò�����صĶ���
	auto self = shared_from_this(); //������this��ָ��
	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);

	_acceptor.async_accept(new_con->GetSocket(), [self, new_con](beast::error_code ec) {
		try {
			//����������ӣ�����������
			if (ec) {
				self->Start();
				return;
			}

			//���������ӣ��½�HttpConnection�����
			new_con->Start();
			self->Start();
		}
		catch (std::exception& exp) {
			std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
		}
	});
}
