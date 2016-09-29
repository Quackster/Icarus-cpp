#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "Request.h"
#include "Response.h"


using boost::asio::ip::tcp;

class NetworkConnection : public std::enable_shared_from_this<NetworkConnection>
{
public:
	NetworkConnection(int connectionID, tcp::socket socket);
	~NetworkConnection();
	void recieve_data();
    void handle_data();
    void send(Response response);
	void write_data(char* data, int length);
    void sendPolicy();
	void disconnected();

private:
	int connectionID;
	tcp::socket socket_;
	enum { max_length = 1024 };
	char buffer[max_length];
	//char data_write[max_length];
};
