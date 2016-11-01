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

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>


using boost::asio::ip::tcp;

class RconConnection : public std::enable_shared_from_this<RconConnection>
{

public:
    RconConnection(tcp::socket socket);
    ~RconConnection();
    void recieveData();
    void sendResponse(std::string content);
    void writeData(const char* data, int length);
    void sendPolicy();
    bool getConnectionState();// { return connectionState; };
    void setConnectionState(bool connectionState);// { this->connectionState = connectionState; };
    tcp::socket &getSocket() { return this->socket; }

private:
    bool connection_state;
    tcp::socket socket;
    enum { maxLength = 512 };
    char buffer[maxLength];
};
