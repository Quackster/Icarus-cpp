#pragma once
#include "game/player/Player.h"
#include "communication/incoming/MessageHandler.h"

class NetworkServer
{
public:
	NetworkServer(boost::asio::io_service& io_service, short port);
	~NetworkServer();
    void startAccept();
    void removeNetworkConnection(NetworkConnection *connection);

private:
    int connection_id;
	tcp::acceptor acceptor;
	tcp::socket socket;
};
