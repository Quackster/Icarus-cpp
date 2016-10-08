#pragma once
#include <boost/asio.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include "communication/streams/Request.h"
#include "communication/streams/Response.h"

#include "communication/outgoing/MessageComposer.h"


using boost::asio::ip::tcp;

class NetworkConnection : public std::enable_shared_from_this<NetworkConnection>
{

public:
    NetworkConnection(int connectionID, tcp::socket socket);
    ~NetworkConnection();
    void recieveData();
    void handleData(Request request);
    void send(Response response);
    void send(MessageComposer &composer);
    void writeData(char* data, int length);
    void sendPolicy();
    int getConnectionId();// { return connectionID; };
    bool getConnectionState();// { return connectionState; };
    void setConnectionState(bool connectionState);// { this->connectionState = connectionState; };
    tcp::socket &getSocket() { return this->socket; };

private:
    int connection_id;
    bool connection_state;
    tcp::socket socket;

    enum { maxLength = 512 };
    char buffer[maxLength];

};
