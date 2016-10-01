#include "stdafx.h"
#include "managers/session/Session.h"

Session::Session(NetworkConnection *session_connection) : networkConnection(session_connection) {
    cout << " [SESSION] Client connected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;
}


Session::~Session() {
    cout << " [SESSION] Client disconnected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;
}

void Session::clear() {

    
}
