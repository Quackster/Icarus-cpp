#include "stdafx.h"
#include "Icarus.h"

/*
Initialise the static variables
*/
SessionManager* Icarus::sessionManager = new SessionManager();

void Icarus::initialiseServer() {
	boost::asio::io_service io_service;
	NetworkServer server(io_service, 30000);
	io_service.run();
}

void Icarus::boot()
{
	printf("Booting server...");
	initialiseServer();
}