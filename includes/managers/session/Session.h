#pragma once
#include "network/NetworkConnection.h"
#include "managers/session/SessionDetails.h"

class Session
{

public:
    Session(NetworkConnection *networkConnection);
    ~Session();
    void clear();
    void send(MessageComposer &composer);

    NetworkConnection *getNetworkConnection() { return this->networkConnection; }
    SessionDetails *getSessionDetails() { return this->sessionDetails; }
    void setSessionDetails(SessionDetails *details) { this->sessionDetails = details; }
    
    string getUniqueId() { return this->unique_id;  }
    void setUniqueId(string unique_id) { this->unique_id = unique_id; }

private:
    NetworkConnection *networkConnection;
    SessionDetails *sessionDetails;
    string unique_id;
};