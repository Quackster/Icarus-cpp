#include <chrono>
#include <thread>

#include "stdafx.h"
#include "boot/Icarus.h"

/*
Initialise the static variables
*/
SessionManager *Icarus::sessionManager;
NetworkServer *Icarus::networkServer;
MessageHandler *Icarus::messageHandler;

/*
Method to boot server with nice print

@return none
*/
void Icarus::boot() {

    cout << endl;
    cout << " ##################################" << endl;
    cout << " ###       Icarus Emulator       ##" << endl;
    cout << " ###        by Quackster         ##" << endl;
    cout << " ##################################" << endl;
    cout << endl;
    cout << " This is a Habbo Hotel private server written in C++ built for Windows, Linux and other Unix-like systems." << endl;
    cout << endl;
    cout << " @author: Quackster" << endl;
    cout << endl;
    
    cout << " @contributors: " << endl     
        << " - LeonHartley " << endl 
        << " - Cecer " << endl;
    
    cout << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    cout << " [BOOT] [SessionManager] Creating session manager " << endl;
    Icarus::sessionManager = new SessionManager();

    cout << " [BOOT] [MessageHandler] Creating message handler " << endl << endl;
    Icarus::messageHandler = new MessageHandler();

    int serverPort = 30000;
    cout << endl  << " [BOOT] [NetworkServer] Starting server on port " << serverPort << endl;
    boost::asio::io_service io_service;
    networkServer = new NetworkServer(io_service, serverPort);
    io_service.run();

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
Deconstructor
*/
Icarus::~Icarus() {
    delete Icarus::sessionManager;
    delete Icarus::networkServer;
    delete Icarus::messageHandler;
}