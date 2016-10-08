#include <chrono>
#include <thread>
#include <string>

#include "stdafx.h"
#include "boot/Icarus.h"
#include "thread/ExampleRunnable.h"


/*
Initialise the static variables
*/
SessionManager *Icarus::sessionManager;
NetworkServer *Icarus::networkServer;
MessageHandler *Icarus::messageHandler;
DatabaseManager *Icarus::databaseManager;
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
    std::this_thread::sleep_for(std::chrono::seconds(1));

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

    Icarus::databaseManager = new DatabaseManager(
        configuration->getString("database.hostname"), 
        configuration->getString("database.port"), 
        configuration->getString("database.username"), 
        configuration->getString("database.password"),
        configuration->getString("database.database"),
        configuration->getInt("database.pool.size"));


    if (Icarus::databaseManager->testConnection()) {
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
    Icarus::sessionManager = new SessionManager();

    std::cout << " [BOOT] [MessageHandler] Creating message handler " << std::endl << std::endl;
    Icarus::messageHandler = new MessageHandler();

    std::cout << std::endl;

    std::cout << " [BOOT] [Game] Creating game instance" << std::endl;
    Icarus::game = new Game();

    for (int i = 0; i < 4; i++) {
        //std::shared_ptr<ExampleRunnable> newRunnable = std::shared_ptr<ExampleRunnable>(i);
        Icarus::getGame()->getGameScheduler()->schedule(std::make_shared<ExampleRunnable>(i));
    }

    Icarus::getGame()->getGameScheduler()->stop();

    /*
        Start server
    */
    int server_port = configuration->getInt("tcp.server.port");
    std::cout << std::endl  << " [BOOT] [NetworkServer] Starting server on port " << server_port << std::endl;
    
    boost::asio::io_service io_service;
    networkServer = new NetworkServer(io_service, server_port);
    io_service.run();
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
SessionManager *Icarus::getSessionManager() { 
    return sessionManager; 
}

/*
Gets the network server instamce

@return: NetworkServer ptr
*/
NetworkServer *Icarus::getNetworkServer() { 
    return networkServer; 
}

/*
Gets the message handler instance

@return: MessageHandler ptr
*/
MessageHandler *Icarus::getMessageHandler() {
    return messageHandler;
}

/*
Gets the database manager instance

@return: DatabaseManager ptr
*/
DatabaseManager *Icarus::getDatabaseManager() {
    return databaseManager;
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
    delete Icarus::sessionManager;
    delete Icarus::networkServer;
    delete Icarus::messageHandler;
    delete Icarus::databaseManager;
    delete Icarus::game;
}