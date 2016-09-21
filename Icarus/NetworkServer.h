#pragma once
#include "Session.h"

class NetworkServer
{
	public:
		NetworkServer(boost::asio::io_service& io_service, short port);
		~NetworkServer();
	private:
		void listen();
		tcp::acceptor acceptor_;
		tcp::socket socket_;
};
