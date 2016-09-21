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
#include "NetworkServer.h"


int main(int argc, char* argv[])
{
	try
	{

		boost::asio::io_service io_service;
		NetworkServer server(io_service, 3242);
		io_service.run();

		printf("sup fam");
	}
	catch (std::exception& e)
	{
		//
	}

	return 0;
}