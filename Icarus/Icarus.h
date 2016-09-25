#pragma once
#include "SessionManager.h"
#include "NetworkServer.h"

class Icarus {
public:
		
	static SessionManager* sessionManager;
	static NetworkServer* networkServer;

	static void boot();
	static void initialiseServer();

	static SessionManager* getSessionManager() {
		return sessionManager;
	}

	static NetworkServer* getNetworkServer() {
		return networkServer;
	}
		
private:
	Icarus() {} // Stop people from trying to init Icarus class, as it's static!

};

