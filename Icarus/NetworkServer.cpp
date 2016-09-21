#include "stdafx.h"
#include "NetworkServer.h"


NetworkServer::NetworkServer(boost::asio::io_service& io_service, short port) : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), socket_(io_service) {
	this->listen();
}


NetworkServer::~NetworkServer()
{
}

void NetworkServer::listen() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {

		if (!ec) {
			printf("Server connected.\n");

			Session* session = new Session(std::make_shared<NetworkConnection>(0, std::move(socket_)));
			session->getNetworkConnection()->recieve_data();

			delete session;
		}

		this->listen();
	});
}
