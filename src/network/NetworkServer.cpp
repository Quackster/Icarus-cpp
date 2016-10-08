#include "stdafx.h"
#include "network/NetworkServer.h"

/*
Network server constructor

@return none
*/
NetworkServer::NetworkServer(boost::asio::io_service& io_service, short port) : 
    acceptor(io_service, tcp::endpoint(tcp::v4(), port)), socket(io_service), connection_id(0) {
    
    this->startAccept();
}

/*
Network server deconstructor

@return none
*/
NetworkServer::~NetworkServer() { 

}

/*
Start accepting clients

@return none
*/
void NetworkServer::startAccept() {
    acceptor.async_accept(socket, [this](boost::system::error_code ec) {

        if (!ec) {
            std::shared_ptr<NetworkConnection> connection = std::make_shared<NetworkConnection>(this->connection_id++, std::move(socket));
            connection->recieveData(); // start with 4 bytes at first
        }

        this->startAccept();
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
}