#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class NetworkConnection : public std::enable_shared_from_this<NetworkConnection>
{
	public:
		NetworkConnection(int connectionID, tcp::socket socket);
		~NetworkConnection();
		void recieve_data();
		void write_data();
		void disconnected();

	private:
		int connectionID;
		tcp::socket socket_;
		enum { max_length = 1024 };
		char data_read[max_length];
		char data_write[max_length];
};
