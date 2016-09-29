#include "stdafx.h"
#include "Session.h"
#include "Icarus.h"

Session::Session(NetworkConnection *networkConnection) : networkConnection(networkConnection) {
    cout << " [SESSION] Created session for connection: " << networkConnection->getConnectionId() << endl;
}

Session::~Session() {
    
    cout << " [SESSION] Removed session for connection: " << networkConnection->getConnectionId() << endl;

    // Dispose network connection
    Icarus::getNetworkServer()->removeNetworkConnection(this->networkConnection);
}

void Session::clear() {

    try {

        
    }
    catch (std::exception &e) {

        cout << " Caught exception: " << e.what() << endl;
    }
}
