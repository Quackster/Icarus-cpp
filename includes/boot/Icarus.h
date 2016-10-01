#pragma once
#include "managers/session/SessionManager.h"
#include "managers/session/Session.h"
#include "network/NetworkServer.h"


class Icarus
{

public:
    static SessionManager *sessionManager;
	static NetworkServer *networkServer;

	static void boot();
	static void initialiseServer(int server_port);

    static SessionManager *getSessionManager() { return sessionManager; }
    static NetworkServer *getNetworkServer() { return networkServer; }

};

