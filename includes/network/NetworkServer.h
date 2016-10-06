#pragma once
#include "game/session/Session.h"
#include "communication/incoming/MessageHandler.h"

class NetworkServer
{
public:
	NetworkServer(boost::asio::io_service& ioService, short port);
	~NetworkServer();
    void startAccept();
    void removeNetworkConnection(NetworkConnection *connection);

private:
    int connectionID;
	tcp::acceptor acceptor;
	tcp::socket socket;
};
