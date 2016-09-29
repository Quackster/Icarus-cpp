#include "stdafx.h"
#include "NetworkServer.h"

/*
Network server constructor

@return none
*/
NetworkServer::NetworkServer(boost::asio::io_service& io_service, short port) : acceptor(io_service, tcp::endpoint(tcp::v4(), port)), socket(io_service) {
	this->start_accept();
    this->connectionID = 0;
}

/*
Network server deconstructor

@return none
*/
NetworkServer::~NetworkServer() { }

/*
Start accepting clients

@return none
*/
void NetworkServer::start_accept() {
	acceptor.async_accept(socket, [this](boost::system::error_code ec) {

		if (!ec) {
            std::make_shared<NetworkConnection>(this->connectionID++, std::move(socket))->recieve_data();
		}

		this->start_accept();
	});
}
