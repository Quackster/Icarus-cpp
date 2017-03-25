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

static std::random_device rd;
static std::mt19937 rng(rd());

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

#if defined(WIN32_LEAN_AND_MEAN)  
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 1400, 800, TRUE); // 800 width, 100 height
#endif

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
        << " - LeonHartley (various ideas and fixes) " << endl
        << " - active911 (mysql database pooling library)" << endl;
         //<< " - Cecer (pathfinder additions) " << endl;
    cout << endl;

    boost::filesystem::path dir("config");

    if (!boost::filesystem::exists("config")) {
        if (!boost::filesystem::create_directory(dir)) {
            cout << "Could not create directory 'config' in this folder" << endl;
            return;
        }
    }

    cout << " [BOOT] [Configuration] Loading configuration" << endl;

    Icarus::database_configuration = new Configuration("config/database.ini");
    Icarus::game_configuration = new Configuration("config/game.ini");
    Icarus::server_configuration = new Configuration("config/server.ini");
    Icarus::log_configuration = new Configuration("config/log.ini");

    cout << " [BOOT] [Configuration] Loaded " << (
        database_configuration->getValues().size() + 
        game_configuration->getValues().size()  + 
        server_configuration->getValues().size() + 
        log_configuration->getValues().size()) << " values" << endl;

    cout << endl;
    cout << " [BOOT] [DatabaseManager] Testing MySQL connection" << endl;

    Icarus::database_manager = new DatabaseManager(
        database_configuration->getString("database.hostname"),
        database_configuration->getString("database.port"),
        database_configuration->getString("database.username"),
        database_configuration->getString("database.password"),
        database_configuration->getString("database.database"),
        database_configuration->getInt("database.pool.size")
    );


    if (Icarus::database_manager->testConnection()) {
        cout << " [BOOT] [DatabaseManager] Connection to MySQL server was successful" << endl;
        cout << " [BOOT] [DatabaseManager] Started database pooling (database name: " << database_configuration->getString("database.database") << ") with a pool size of " << database_configuration->getInt("database.pool.size") << endl;
    }
    else {
        cout << " [ATTENTION] Connection to mysql server failed " << endl;
        return;
    }

    cout << endl;
    cout << " [BOOT] [SessionManager] Creating session manager " << endl;
    Icarus::player_manager = new PlayerManager();
    cout << " [BOOT] [MessageHandler] Creating message handler " << endl << endl;
    Icarus::message_handler = new MessageHandler();
    cout << " [BOOT] [Game] Creating game instance" << endl;
    Icarus::game = new Game();
    game->createGame();

    int server_port = server_configuration->getInt("tcp.server.port");
    int rcon_port = server_configuration->getInt("rcon.server.port");

    cout << endl << " [BOOT] [ReconServer] Starting rcon server on port " << rcon_port;
    cout << endl  << " [BOOT] [NetworkServer] Starting main server on port " << server_port << endl;

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
    Get random number between two points

    @param lower number
    @param higher number
    @return random selected number
*/
const int Icarus::getRandomNumber(int a, int b) {
    std::uniform_int_distribution<int> gen(a, b); // uniform, unbiased
    return gen(rng);
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