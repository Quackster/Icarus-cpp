#pragma once
#include "game/player/PlayerManager.h"
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
    static PlayerManager *getPlayerManager();// { return sessionManager; }
    static NetworkServer *getNetworkServer();
    static MessageHandler *getMessageHandler();// { return networkServer; }
    static DatabaseManager *getDatabaseManager();
    static Configuration *getConfiguration();
    static Game *getGame();

private:
    static PlayerManager *player_manager;
    static NetworkServer *network_server;
    static MessageHandler *message_handler;
    static DatabaseManager *database_manager;
    static Configuration *configuration;
    static Game *game;

};

