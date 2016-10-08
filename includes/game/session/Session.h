#pragma once
#include "network/NetworkConnection.h"
#include "game/session/SessionDetails.h"

class Session
{

public:
    Session(NetworkConnection *network_connection);
    ~Session();
    void clear();
    void send(MessageComposer &composer);

    NetworkConnection *getNetworkConnection() { return this->network_connection; }
    SessionDetails *getDetails() { return this->session_details; }
    void setSessionDetails(SessionDetails *details) { this->session_details = details; }
    
    std::string getUniqueId() { return this->unique_id;  }
    void setUniqueId(std::string unique_id) { this->unique_id = unique_id; }

private:
    NetworkConnection *network_connection;
    SessionDetails *session_details;
    std::string unique_id;
};