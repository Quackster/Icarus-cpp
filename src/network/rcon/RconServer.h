/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <boost/asio.hpp>

#include "game/player/Player.h"

class RconServer
{
public:
    RconServer(boost::asio::io_service& io_service, std::string host, short port);
    ~RconServer();
    void startAccept();

private:
    int connection_id;
    tcp::acceptor acceptor;
    tcp::socket socket;
};
