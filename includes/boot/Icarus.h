#pragma once
#include "game/session/SessionManager.h"
#include "database/DatabaseManager.h"
#include "network/NetworkServer.h"
#include "communication/incoming/MessageHandler.h"
#include "misc/Configuration.h"
#include "game/Game.h"

class Icarus
{

public:
    ~Icarus();
	static void boot();
    static SessionManager *getSessionManager();// { return sessionManager; }
    static NetworkServer *getNetworkServer();
    static MessageHandler *getMessageHandler();// { return networkServer; }
    static DatabaseManager *getDatabaseManager();
    static Configuration *getConfiguration();
    static Game *getGame();

private:
    static SessionManager *sessionManager;
    static NetworkServer *networkServer;
    static MessageHandler *messageHandler;
    static DatabaseManager *databaseManager;
    static Configuration *configuration;
    static Game *game;

};

