#pragma once
#include "network/NetworkConnection.h"
#include "managers/session/SessionDetails.h"

class Session
{

public:
    Session(NetworkConnection *networkConnection);
    ~Session();
    void send(MessageComposer &composer);
    void clear();

    NetworkConnection *getNetworkConnection() { return networkConnection; }
    SessionDetails *getSessionDetails() { return sessionDetails; }
    void setSessionDetails(SessionDetails *details) { sessionDetails = details; }

private:
    NetworkConnection *networkConnection;
    SessionDetails *sessionDetails;
    
};