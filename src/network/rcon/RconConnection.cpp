/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include <sstream>

#include "misc/Utilities.h"
#include "boot/Icarus.h"
#include "RconConnection.h"


/*
RconConnection constructor

@param connection id
@param tcp::socket connection socket

@return instance
*/
RconConnection::RconConnection(tcp::socket socket) :
    socket(std::move(socket)), 
    connection_state(true) { }

RconConnection::~RconConnection() { }

/*
Receive data handle

@return none
*/
void RconConnection::recieveData() {

    if (!this->connection_state) {
        return; // Person disconnected, stop listing for data, in case somehow it still is (when it shouldn't) ;)
    }

    auto self(shared_from_this());

    // only 4 bytes for now, the length
    socket.async_receive(boost::asio::buffer(buffer, maxLength), [this, self](boost::system::error_code ec, std::size_t length) {

        if (!ec) {

            std::string rcon_command = std::string(buffer);

            if (rcon_command.find("password=" + Icarus::getServerConfiguration()->getString("rcon.server.password")) == std::string::npos) {
                return;
            }

            std::vector<std::string> command_parts = Utilities::split(rcon_command, ';');

            std::string command = command_parts[1];
            std::string command_data = command_parts[2];

            cout << "Command: " << command << ", command data: " << command_data << endl;

            /*this->sendResponse(
                "<title>testing123"
                "</title><h2>hello</h2>"
                "<p>parapgraph</p>"
                "<marquee>" + std::string(buffer) + "</marquee>");*/

            
            
        }
    });
}

/*
    Sends a HTTP response with the right amount of length appended

    @param std::string content
    @return none
*/
void RconConnection::sendResponse(std::string content) {

    /*std::stringstream ss;

    ss << "HTTP/1.1 200 OK\n"
    << "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
    << "Server: Apache/2.2.3\n"
    << "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
    << "ETag: \"56d-9989200-1132c580\"\n"
    << "Content-Type: text/html\n"
    << "Content-Length: "
    << std::to_string(content.length())
    << "\n"
    << "Accept-Ranges: bytes\n"
    << "Connection: close\n"
    << "\n"
    << content;

    std::string response = ss.str();

    this->writeData(response.c_str(), response.length());*/
}

/*
Write data handle

@return none
*/
void RconConnection::writeData(const char* data, int length) {

    if (!this->connection_state) {
        return; // Person disconnected, stop writing data...
    }


    auto self(shared_from_this());

    boost::asio::async_write(socket, boost::asio::buffer(data, /*this->max_length*/length), [this, self, data](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            // send success
        }
    });
}



/*
Send policy to the socket

@return void

*/
void RconConnection::sendPolicy() {
    char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
    this->writeData(policy, (int)strlen(policy) + 1);

    // Define variables for boost recv
    auto self(shared_from_this());

    // Read rest of policy request
    socket.async_receive(boost::asio::buffer(buffer, 18), [this, self](boost::system::error_code ec, std::size_t length) {});
}

/*
Gets the connection state of the user. True for connected, false for disconnected

@return connection flag
*/
bool RconConnection::getConnectionState() { 
    return connection_state; 
};

/*
Sets the connection state, if set to false, the user will no longer receive
any incoming packets

@return none
*/
void RconConnection::setConnectionState(bool connection_state) {
    this->connection_state = connection_state; 
};
