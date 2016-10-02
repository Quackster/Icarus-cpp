#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "communication/streams/Request.h"
#include "communication/streams/Response.h"

#include "communication/outgoing/MessageComposer.h"


using boost::asio::ip::tcp;

class NetworkConnection : public std::enable_shared_from_this<NetworkConnection>
{

public:
    NetworkConnection(int connectionID, tcp::socket socket);
    ~NetworkConnection();
    void recieve_data();
    void handle_data(Request request);
    void send(Response response);
    void send(MessageComposer *composer);
    void write_data(char* data, int length);
    void sendPolicy();
    void disconnected();
    int getConnectionId() { return connectionID; };
    bool getConnectionState() { return connectionState; };
    void setConnectionState(bool connectionState) { this->connectionState = connectionState; };

private:
    int connectionID;
    bool connectionState;
    tcp::socket socket;

    enum { max_length = 512 };
    char buffer[max_length];

};
