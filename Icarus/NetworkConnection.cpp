#include "stdafx.h"
#include "NetworkConnection.h"


NetworkConnection::NetworkConnection(tcp::socket socket) : socket_(std::move(socket))
{
}


NetworkConnection::~NetworkConnection()
{
}

void NetworkConnection::recieve_data() {

	auto self(shared_from_this());

	socket_.async_read_some(boost::asio::buffer(this->data_read, this->max_length), 
		[this, self](boost::system::error_code ec, std::size_t length) {

		if (!ec) {

			printf("%s\n", data_read);

			// Read data again, to check if the client had disconnected.
			this->recieve_data();
		}
		else {
			printf("disconnection \n");
		}
	});
}

void NetworkConnection::write_data(/*std::size_t length*/) {

	auto self(shared_from_this());

	// Asynchrnous write to socket
	boost::asio::async_write(socket_, boost::asio::buffer(this->data_write, this->max_length), 
		[this, self](boost::system::error_code ec, std::size_t length) {

		// If there's no error code, continue with writing
		if (!ec) {
			printf("%s\n", data_read);
		}
	});
}

void NetworkConnection::disconnected() {


}
