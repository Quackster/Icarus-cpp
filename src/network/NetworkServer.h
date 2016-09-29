#pragma once
#include "Session.h"

class NetworkServer
{
	public:
		NetworkServer(boost::asio::io_service& io_service, short port);
		~NetworkServer();
	private:
		void listen();
		tcp::acceptor acceptor;
		tcp::socket socket;
};
