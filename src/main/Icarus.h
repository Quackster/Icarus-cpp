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
		static void initialiseServer();

        static SessionManager *getSessionManager() { return sessionManager; }
        static NetworkServer *getNetworkServer() { return networkServer; }
};

