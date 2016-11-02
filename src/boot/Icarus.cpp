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
#include <string>

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
Configuration *Icarus::configuration;
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
    //std::this_thread::sleep_for(std::chrono::seconds(1));

    /*
        Load configuration
    */
    std::cout << " [BOOT] [Configuration] Loading configuration" << std::endl;
    Icarus::configuration = new Configuration("configuration.ini");
    std::cout << " [BOOT] [Configuration] Loaded " << configuration->getValues()->size() << " values" << std::endl;

    /*
        Test MySQL connection
    */
    std::cout << std::endl;
    std::cout << " [BOOT] [DatabaseManager] Testing MySQL connection" << std::endl;

    Icarus::database_manager = new DatabaseManager(
        configuration->getString("database.hostname"), 
        configuration->getString("database.port"), 
        configuration->getString("database.username"), 
        configuration->getString("database.password"),
        configuration->getString("database.database"),
        configuration->getInt("database.pool.size"));


    if (Icarus::database_manager->testConnection()) {
        std::cout << " [BOOT] [DatabaseManager] Connection to MySQL server was successful" << std::endl;
        std::cout << " [BOOT] [DatabaseManager] Started database pooling (database name: " << configuration->getString("database.database") << ") with a pool size of " << configuration->getInt("database.pool.size") << std::endl;
    } else {
        std::cout << " [ATTENTION] Connection to mysql server failed " << std::endl;
        return;
    }

    /*
        Load managers
    */

    std::cout << std::endl;
    std::cout << " [BOOT] [SessionManager] Creating session manager " << std::endl;
    Icarus::player_manager = new PlayerManager();

    std::cout << " [BOOT] [MessageHandler] Creating message handler " << std::endl << std::endl;
    Icarus::message_handler = new MessageHandler();

    std::cout << std::endl;

    std::cout << " [BOOT] [Game] Creating game instance" << std::endl;
    Icarus::game = new Game();
    game->createGame();

    /*for (int i = 0; i < 10; i++) {
        //std::shared_ptr<ExampleRunnable> newRunnable = std::shared_ptr<ExampleRunnable>(i);
        Icarus::getGame()->getGameScheduler()->schedule(std::make_shared<ExampleRunnable>(i));
    }

    Icarus::getGame()->getGameScheduler()->stop();*/

    /*
        Start server
    */
    int server_port = configuration->getInt("tcp.server.port");
    int rcon_port = configuration->getInt("rcon.server.port");

    std::cout << std::endl << " [BOOT] [ReconServer] Starting rcon server on port " << rcon_port;
    std::cout << std::endl  << " [BOOT] [NetworkServer] Starting main server on port " << server_port << std::endl;

    boost::asio::io_service io_service;
    network_server = new NetworkServer(io_service, configuration->getString("tcp.server.host"), server_port);
    
    boost::asio::io_service rcon_service;
    auto rcon_server = new RconServer(rcon_service, configuration->getString("rcon.server.host"), rcon_port);

    boost::thread_group threads;
    threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
    rcon_service.run();
    threads.join_all();

    //io_service.run();
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
Gets the configuration instance

@return: Configuration ptr
*/
Configuration *Icarus::getConfiguration() {
    return configuration;
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
}