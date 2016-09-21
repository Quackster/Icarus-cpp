//
// async_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "stdafx.h"
#include "sessionConnection.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class server
{
public:
	server(boost::asio::io_service& io_service, short port) : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), socket_(io_service) {
		do_accept();
	}

private:

	void do_accept()  {
		acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
			
			if (!ec) {
				printf("Server connected.\n");
				std::make_shared<sessionConnection>(std::move(socket_))->recieve_data();
			}

			do_accept();
		});
	}

	tcp::acceptor acceptor_;
	tcp::socket socket_;
};

int main(int argc, char* argv[])
{
	try
	{

		boost::asio::io_service io_service;

		server s(io_service, 3242);

		io_service.run();
	}
	catch (std::exception& e)
	{
		//
	}

	return 0;
}