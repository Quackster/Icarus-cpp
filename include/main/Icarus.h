#pragma once
#include "Session.h"
#include "NetworkServer.h"
#include "SessionManager.h"

class Icarus
{

public:
    static SessionManager *sessionManager;
	static NetworkServer *networkServer;

	static void boot();
	static void initialiseServer(int server_port);

    static SessionManager *getSessionManager() { return NULL; }
    static NetworkServer *getNetworkServer() { return networkServer; }

};

