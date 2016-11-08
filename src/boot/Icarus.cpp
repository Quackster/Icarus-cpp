/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include <chrono>
#include <thread>
#include <ctime>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#include "stdafx.h"
#include "Icarus.h"

#include "network/rcon/RconServer.h"

//#include "thread/ExampleRunnable.h"


/*
Define static variables
*/
PlayerManager *Icarus::player_manager;
NetworkServer *Icarus::network_server;
MessageHandler *Icarus::message_handler;
DatabaseManager *Icarus::database_manager;

Configuration *Icarus::database_configuration;
Configuration *Icarus::game_configuration;
Configuration *Icarus::log_configuration;
Configuration *Icarus::server_configuration;

Game *Icarus::game;

/*
Method to boot server with nice print

@return none
*/
void Icarus::boot() {

    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;

    std::cout << std::endl;
    std::cout << " ##################################" << std::endl;
    std::cout << " ###       Icarus Emulator       ##" << std::endl;
    std::cout << " ###        by Quackster         ##" << std::endl;
    std::cout << " ##################################" << std::endl;
    std::cout << std::endl;
    std::cout << " This is a server written in C++ built for Windows, Linux and other Unix-like systems." << std::endl;
    std::cout << std::endl;
    std::cout << " @author: Quackster" << std::endl;
    std::cout << std::endl;
    std::cout << " @contributors: " << std::endl 
         << " - active911 " << std::endl
         << " - LeonHartley " << std::endl 
         << " - Cecer " << std::endl;
    std::cout << std::endl;

    boost::filesystem::path dir("config");

    if (!boost::filesystem::exists("config")) {
        if (!boost::filesystem::create_directory(dir)) {
            std::cout << "Could not create directory 'config' in this folder" << std::endl;
            return;
        }
    }

    std::cout << " [BOOT] [Configuration] Loading configuration" << std::endl;

    Icarus::database_configuration = new Configuration("config/database.ini");
    Icarus::game_configuration = new Configuration("config/game.ini");
    Icarus::server_configuration = new Configuration("config/server.ini");
    Icarus::log_configuration = new Configuration("config/log.ini");

    std::cout << " [BOOT] [Configuration] Loaded " << (database_configuration->getValues()->size() + game_configuration->getValues()->size()  + server_configuration->getValues()->size() + log_configuration->getValues()->size()) << " values" << std::endl;
    std::cout << std::endl;
    std::cout << " [BOOT] [DatabaseManager] Testing MySQL connection" << std::endl;

    Icarus::database_manager = new DatabaseManager(
        database_configuration->getString("database.hostname"),
        database_configuration->getString("database.port"),
        database_configuration->getString("database.username"),
        database_configuration->getString("database.password"),
        database_configuration->getString("database.database"),
        database_configuration->getInt("database.pool.size")
    );


    if (Icarus::database_manager->testConnection()) {
        std::cout << " [BOOT] [DatabaseManager] Connection to MySQL server was successful" << std::endl;
        std::cout << " [BOOT] [DatabaseManager] Started database pooling (database name: " << database_configuration->getString("database.database") << ") with a pool size of " << database_configuration->getInt("database.pool.size") << std::endl;
    }
    else {
        std::cout << " [ATTENTION] Connection to mysql server failed " << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << " [BOOT] [SessionManager] Creating session manager " << std::endl;
    Icarus::player_manager = new PlayerManager();
    std::cout << " [BOOT] [MessageHandler] Creating message handler " << std::endl << std::endl;
    Icarus::message_handler = new MessageHandler();
    std::cout << " [BOOT] [Game] Creating game instance" << std::endl;
    Icarus::game = new Game();
    game->createGame();

    int server_port = server_configuration->getInt("tcp.server.port");
    int rcon_port = server_configuration->getInt("rcon.server.port");

    std::cout << std::endl << " [BOOT] [ReconServer] Starting rcon server on port " << rcon_port;
    std::cout << std::endl  << " [BOOT] [NetworkServer] Starting main server on port " << server_port << std::endl;

    boost::asio::io_service io_service;
    network_server = new NetworkServer(io_service, server_configuration->getString("tcp.server.host"), server_port);
    
    boost::asio::io_service rcon_service;
    auto rcon_server = new RconServer(rcon_service, server_configuration->getString("rcon.server.host"), rcon_port);

    boost::thread_group threads;
    threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
    rcon_service.run();
    threads.join_all();
}

/*
    Get current Unix timestamp

    @return long
*/
long const Icarus::getUnixTimestamp() {
    time_t t = std::time(0);
    return static_cast<long> (t);
}

/*
    Gets the game instance

    @return: Game ptr
*/
Game *Icarus::getGame() {
    return game;
}

/*
    Gets the session manager instance

    @return: SessionManager ptr
*/
PlayerManager *Icarus::getPlayerManager() {
    return player_manager;
}

/*
    Gets the network server instamce

    @return: NetworkServer ptr
*/
NetworkServer *Icarus::getNetworkServer() { 
    return network_server; 
}

/*
    Gets the message handler instance

    @return: MessageHandler ptr
*/
MessageHandler *Icarus::getMessageHandler() {
    return message_handler;
}

/*
    Gets the database manager instance

    @return: DatabaseManager ptr
*/
DatabaseManager *Icarus::getDatabaseManager() {
    return database_manager;
}

/*
    Gets the log configuration instance

    @return: Configuration ptr
*/
Configuration *Icarus::getLogConfiguration() {
    return log_configuration;
}

/*
Gets the database configuration instance

@return: Configuration ptr
*/
Configuration *Icarus::getDatabaseConfiguration() {
    return database_configuration;
}

/*
    Gets the game configuration instance

    @return: Configuration ptr
*/
Configuration *Icarus::getGameConfiguration() {
    return game_configuration;
}

/*
Gets the server configuration instance

@return: Configuration ptr
*/
Configuration *Icarus::getServerConfiguration() {
    return server_configuration;
}

/*
Deconstructor
*/
Icarus::~Icarus() {
    delete Icarus::player_manager;
    delete Icarus::network_server;
    delete Icarus::message_handler;
    delete Icarus::database_manager;
    delete Icarus::game;

    delete Icarus::game_configuration;
    delete Icarus::database_configuration;
    delete Icarus::server_configuration;
    delete Icarus::log_configuration;
}