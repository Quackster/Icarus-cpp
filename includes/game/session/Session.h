#pragma once
#include "network/NetworkConnection.h"
#include "game/session/SessionDetails.h"

class Session
{

public:
    Session(NetworkConnection *networkConnection);
    ~Session();
    void clear();
    void send(MessageComposer &composer);

    NetworkConnection *getNetworkConnection() { return this->networkConnection; }
    SessionDetails *getDetails() { return this->sessionDetails; }
    void setSessionDetails(SessionDetails *details) { this->sessionDetails = details; }
    
    std::string getUniqueId() { return this->uniqueId;  }
    void setUniqueId(std::string unique_id) { this->uniqueId = unique_id; }

private:
    NetworkConnection *networkConnection;
    SessionDetails *sessionDetails;
    std::string uniqueId;
};