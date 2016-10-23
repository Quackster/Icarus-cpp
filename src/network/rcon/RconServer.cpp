/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "RconServer.h"
#include "RconConnection.h"

/*
Network server constructor

@return none
*/
RconServer::RconServer(boost::asio::io_service& io_service, short port) :
    acceptor(io_service, tcp::endpoint(tcp::v4(), port)), socket(io_service), connection_id(0) {
    
    this->startAccept();
}

/*
Network server deconstructor

@return none
*/
RconServer::~RconServer() {

}

/*
Start accepting clients

@return none
*/
void RconServer::startAccept() {
    acceptor.async_accept(socket, [this](boost::system::error_code ec) {

        if (!ec) {
            std::shared_ptr<RconConnection> connection = std::make_shared<RconConnection>(std::move(socket));
            connection->recieveData(); // start with 4 bytes at first
        }

        this->startAccept();
    });
}