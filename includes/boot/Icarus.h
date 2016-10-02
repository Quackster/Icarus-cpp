#pragma once
#include "managers/session/SessionManager.h"
#include "network/NetworkServer.h"
#include "communication/incoming/MessageHandler.h"


class Icarus
{

public:
    ~Icarus();
	static void boot();
	static void initialiseServer(int server_port);
    static SessionManager *getSessionManager();// { return sessionManager; }
    static NetworkServer *getNetworkServer();
    static MessageHandler *getMessageHandler();// { return networkServer; }

private:
    static SessionManager *sessionManager;
    static NetworkServer *networkServer;
    static MessageHandler *messageHandler;

};

