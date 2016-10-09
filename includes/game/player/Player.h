#pragma once

#include "network/NetworkConnection.h"
#include "game/entities/Entity.h"

class Player : public Entity {

public:
    Player(NetworkConnection *network_connection);
    ~Player();
    void login();
    void clear();
    void send(MessageComposer &composer);

    NetworkConnection *getNetworkConnection() { return this->network_connection; }
    EntityDetails *getDetails() { return this->session_details; }
    void setDetails(EntityDetails *details) { this->session_details = details; }
    
    std::string getUniqueId() { return this->unique_id;  }
    void setUniqueId(std::string unique_id) { this->unique_id = unique_id; }

    EntityType getEntityType() { EntityType type = PLAYER; return type; }

private:
    NetworkConnection *network_connection;
    EntityDetails *session_details;
    std::string unique_id;
};