#include "stdafx.h"
#include "Icarus.h"
#include "NetworkServer.h"

/*
Initialise the static variables
*/
SessionManager* Icarus::sessionManager = new SessionManager();
NetworkServer* Icarus::networkServer = new NetworkServer();

/*
Method to call when starting the server

@return none
*/
void Icarus::initialiseServer() {
	Icarus::networkServer->startServer(30000);
}

/*
Console application boot appearance, along with handling the startup of the server

@return none
*/
void Icarus::boot() {
	printf("\n");
	printf(" ##################################\n");
	printf(" ###       Icarus Emulator       ##\n");
	printf(" ###        by Quackster         ##\n");
	printf(" ##################################\n");
	printf("\n");
	printf(" This is a Habbo Hotel private server written in C++ built for Windows.\n");
	printf("\n");

	printf(" [BOOT] Starting server\n");
	initialiseServer();

	printf(" [BOOT] Finished!\n");
	printf("\n");
}