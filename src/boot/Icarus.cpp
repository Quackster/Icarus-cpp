#include "stdafx.h"
#include "boot/Icarus.h"

/*
Initialise the static variables
*/
SessionManager* Icarus::sessionManager = new SessionManager();
NetworkServer* Icarus::networkServer;

/*
Call Boost Asio API to start server

@return none
*/
void Icarus::initialiseServer(int serverPort) {
    boost::asio::io_service io_service;
    networkServer = new NetworkServer(io_service, serverPort);
    io_service.run();
}

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
    cout << " This is a Habbo Hotel private server written in C++ built for Windows." << endl;
    cout << endl;

    int serverPort = 30000;
    cout << " [BOOT] Starting server on port: " << serverPort << endl;
    initialiseServer(serverPort);

}