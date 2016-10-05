#include <chrono>
#include <thread>
#include <string>

#include "stdafx.h"
#include "boot/Icarus.h"
#include "thread/ExampleRunnable.h"
using namespace std;

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

    cout << endl;
    cout << " ##################################" << endl;
    cout << " ###       Icarus Emulator       ##" << endl;
    cout << " ###        by Quackster         ##" << endl;
    cout << " ##################################" << endl;
    cout << endl;
    cout << " This is a server written in C++ built for Windows, Linux and other Unix-like systems." << endl;
    cout << endl;
    cout << " @author: Quackster" << endl;
    cout << endl;
    cout << " @contributors: " << endl 
         << " - active911 " << endl
         << " - LeonHartley " << endl 
         << " - Cecer " << endl;
    cout << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /*
        Load configuration
    */
    cout << " [BOOT] [Configuration] Loading configuration" << endl;
    Icarus::configuration = new Configuration("configuration.ini");
    cout << " [BOOT] [Configuration] Loaded " << configuration->getValues()->size() << " values" << endl;

    /*
        Test MySQL connection
    */
    cout << endl;
    cout << " [BOOT] [DatabaseManager] Testing MySQL connection" << endl;

    Icarus::databaseManager = new DatabaseManager(
        configuration->getString("database.hostname"), 
        configuration->getString("database.port"), 
        configuration->getString("database.username"), 
        configuration->getString("database.password"),
        configuration->getString("database.database"),
        configuration->getInt("database.pool.size"));


    if (Icarus::databaseManager->testConnection()) {
        cout << " [BOOT] [DatabaseManager] Connection to MySQL server was successful" << endl;
        cout << " [BOOT] [DatabaseManager] Started database pooling (database name: " << configuration->getString("database.database") << ") with a pool size of " << configuration->getInt("database.pool.size") << endl;
    } else {
        cout << " [ATTENTION] Connection to mysql server failed " << endl;
        return;
    }

    /*
        Load managers
    */

    cout << endl;
    cout << " [BOOT] [SessionManager] Creating session manager " << endl;
    Icarus::sessionManager = new SessionManager();

    cout << " [BOOT] [MessageHandler] Creating message handler " << endl << endl;
    Icarus::messageHandler = new MessageHandler();

    cout << endl;

    cout << " [BOOT] [Game] Creating game instance" << endl;
    Icarus::game = new Game();

    ExampleRunnable *runnable = new ExampleRunnable(0);
    game->getExecutorService()->schedule(runnable);

    /*
        Start server
    */
    int serverPort = configuration->getInt("tcp.server.port");
    cout << endl  << " [BOOT] [NetworkServer] Starting server on port " << serverPort << endl;
    
    boost::asio::io_service io_service;
    networkServer = new NetworkServer(io_service, serverPort);
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