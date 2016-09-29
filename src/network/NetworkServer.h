#pragma once
#include "Session.h"

class NetworkServer
{
public:
	NetworkServer(boost::asio::io_service& io_service, short port);
	~NetworkServer();
    void start_accept();
    void removeNetworkConnection(NetworkConnection *connection);
private:
    int connectionID;
	tcp::acceptor acceptor;
	tcp::socket socket;
};
