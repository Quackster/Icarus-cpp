#include "stdafx.h"
#include "Icarus.h"
#include "NetworkServer.h"

/*
Initialise the static variables
*/
SessionManager* Icarus::sessionManager = new SessionManager();
NetworkServer* Icarus::networkServer = new NetworkServer();

/*
Method to call when starting the server

@return none
*/
void Icarus::initialiseServer() {
    Icarus::networkServer->startServer(30000);
}

/*
Console application boot appearance, along with handling the startup of the server

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

    cout << " [BOOT] Starting server" << endl;
    initialiseServer();

    cout << " [BOOT] Finished!" << endl;
    cout << endl;
}