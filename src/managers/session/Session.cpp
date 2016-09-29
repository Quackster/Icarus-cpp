#include "stdafx.h"
#include "Session.h"

Session::Session(NetworkConnection *session_connection) : networkConnection(session_connection) {
    cout << "Client connected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;
}


Session::~Session() {
    cout << "Client disconnected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;
}

void Session::clear() {

	
}
