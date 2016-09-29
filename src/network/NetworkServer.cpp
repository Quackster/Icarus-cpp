#include "stdafx.h"
#include "NetworkServer.h"


NetworkServer::NetworkServer(boost::asio::io_service& io_service, short port) : acceptor(io_service, tcp::endpoint(tcp::v4(), port)), socket(io_service) {
	this->listen();
}

NetworkServer::~NetworkServer()
{
}

void NetworkServer::listen() {
	acceptor.async_accept(socket, [this](boost::system::error_code ec) {

		if (!ec) {
            std::make_shared<NetworkConnection>(0, std::move(socket))->recieve_data();
		}

		this->listen();
	});
}
