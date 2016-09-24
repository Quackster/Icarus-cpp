#include "stdafx.h"
#include "Icarus.h"
#include "NetworkServer.h";

SessionManager* Icarus::sessionManager = new SessionManager();

void Icarus::initialiseServer() {
	NetworkServer server = NetworkServer(30000);
	server.startServer();
}

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