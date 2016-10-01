#include "stdafx.h"
#include "network/NetworkServer.h"

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
            shared_ptr<NetworkConnection> connection = std::make_shared<NetworkConnection>(this->connectionID++, std::move(socket));
            connection->recieve_data(); // start with 4 bytes at first
        }

        this->start_accept();
    });
}

/**
Stops network connection from listening for more packets and deletes it from memory
@param NetworkConnection pointer to delete
@return none
*/
void NetworkServer::removeNetworkConnection(NetworkConnection *connection) {

    // Tell connnection to stop looping for more incoming packets
    connection->setConnectionState(false);

    // Clear connection from memory
    //delete connection;
}