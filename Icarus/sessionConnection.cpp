#include "stdafx.h"
#include "sessionConnection.h"


sessionConnection::sessionConnection(tcp::socket socket) : socket_(std::move(socket))
{
}


sessionConnection::~sessionConnection()
{
}

void sessionConnection::read_data() {

	auto self(shared_from_this());

	socket_.async_read_some(boost::asio::buffer(this->data_read, this->max_length), [this, self](boost::system::error_code ec, std::size_t length) {

		if (!ec) {
			printf("%s\n", data_read);
			this->read_data();
		}
		else {
			printf("disconnection \n");
		}
	});
}

void sessionConnection::write_data(std::size_t length) {

	auto self(shared_from_this());
	boost::asio::async_write(socket_, boost::asio::buffer(this->data_read, this->max_length), [this, self](boost::system::error_code ec, std::size_t length) {

		if (ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset) {
			printf("sesison disconnect/n");
		}
		else {
			printf("%s\n", data_read);
		}
	});
}