#pragma once
#include "network/NetworkConnection.h"
#include "game/player/PlayerDetails.h"

class Player
{

public:
    Player(NetworkConnection *network_connection);
    ~Player();
    void login();
    void clear();
    void send(MessageComposer &composer);

    NetworkConnection *getNetworkConnection() { return this->network_connection; }
    PlayerDetails *getDetails() { return this->session_details; }
    void setSessionDetails(PlayerDetails *details) { this->session_details = details; }
    
    std::string getUniqueId() { return this->unique_id;  }
    void setUniqueId(std::string unique_id) { this->unique_id = unique_id; }

private:
    NetworkConnection *network_connection;
    PlayerDetails *session_details;
    std::string unique_id;
};