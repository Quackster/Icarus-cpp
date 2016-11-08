/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/player/PlayerManager.h"
#include "database/DatabaseManager.h"
#include "network/NetworkServer.h"
#include "communication/incoming/MessageHandler.h"
#include "misc/Configuration.h"
#include "game/Game.h"

class PlayerManager;
class NetworkServer;
class MessageHandler;
class DatabaseManager;
class Configuration;
class Game;

class Icarus
{

public:
    ~Icarus();
    static void boot();
    static const long getUnixTimestamp();
    static PlayerManager *getPlayerManager();// { return sessionManager; }
    static NetworkServer *getNetworkServer();
    static MessageHandler *getMessageHandler();// { return networkServer; }
    static DatabaseManager *getDatabaseManager();

    static Configuration *getDatabaseConfiguration();
    static Configuration *getGameConfiguration();
    static Configuration *getLogConfiguration();
    static Configuration *getServerConfiguration();

    static Game *getGame();

private:
    static PlayerManager *player_manager;
    static NetworkServer *network_server;
    static MessageHandler *message_handler;
    static DatabaseManager *database_manager;

    static Configuration *server_configuration;
    static Configuration *game_configuration;
    static Configuration *log_configuration;
    static Configuration *database_configuration;

    static Game *game;


};

