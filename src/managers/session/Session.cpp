#include "stdafx.h"
#include "managers/session/Session.h"
#include "managers/session/SessionDetails.h"

/*
    Session constructor

    @param NetworkConnection ptr
    @return session instance
*/
Session::Session(NetworkConnection *session_connection) : networkConnection(session_connection) {
    this->sessionDetails = nullptr;
    cout << " [SESSION] Client connected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;
}


/*
    Send message composer to the session's socket

    @param MessageComposer ptr
    @return none
*/
void Session::send(MessageComposer *composer) {
    this->networkConnection->send(composer);
}

/*
    Clear session of any responsibilities

    @return none
*/
void Session::clear() {

    
}

/*
    Session deconstructor, called when session disconnects, 
    is deleted from SessionManager class

    networkManager->connectionState has already been set to false 
    so there won't be any more packet receiving
*/
Session::~Session() {
    cout << " [SESSION] Client disconnected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;

    delete sessionDetails;
}
