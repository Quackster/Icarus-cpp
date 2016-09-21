#include "stdafx.h"
#include "Icarus.h"


void Icarus::initialiseServer() {
	boost::asio::io_service io_service;
	NetworkServer server(io_service, 3242);
	io_service.run();
}

void Icarus::boot()
{
	printf("Booting server...");
	initialiseServer();
}