/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/player/Player.h"
#include "communication/incoming/MessageHandler.h"

class NetworkServer
{
public:
	NetworkServer(boost::asio::io_service& io_service, std::string host, short port);
	~NetworkServer();
    void startAccept();
    void removeNetworkConnection(NetworkConnection *connection);

private:
    int connection_id;
	tcp::acceptor acceptor;
	tcp::socket socket;
};
