#pragma once
#include "managers/session/SessionManager.h"
#include "database/DatabaseManager.h"
#include "network/NetworkServer.h"
#include "communication/incoming/MessageHandler.h"

class Icarus
{

public:
    ~Icarus();
	static void boot();
    static SessionManager *getSessionManager();// { return sessionManager; }
    static NetworkServer *getNetworkServer();
    static MessageHandler *getMessageHandler();// { return networkServer; }
    static DatabaseManager getDatabaseManager();

private:
    static SessionManager *sessionManager;
    static NetworkServer *networkServer;
    static MessageHandler *messageHandler;
    static DatabaseManager databaseManager;

};

