#include "stdafx.h"
#include "Icarus.h"


void Icarus::initialiseServer() {
	NetworkServer server = NetworkServer(3242);
	server.startServer();
}

void Icarus::boot() {
	printf("Booting server...\n");
	initialiseServer();
}