/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "network/NetworkConnection.h"
#include "game/entities/Entity.h"

class Player : public Entity {

public:
    Player(NetworkConnection *network_connection);
    ~Player();
    void login();
    void clear();
    void send(const MessageComposer &composer);

    NetworkConnection *getNetworkConnection() { return this->network_connection; }

    std::string getUniqueId() { return this->unique_id;  }
    void setUniqueId(std::string unique_id) { this->unique_id = unique_id; }

    EntityType getEntityType() { EntityType type = PLAYER; return type; }    

    EntityDetails *getDetails() { return this->session_details; }
    void setDetails(EntityDetails *details) { this->session_details = details; }

    RoomUser *getRoomUser() { return this->room_user; }
    void setRoomUser(RoomUser* room_user) { this->room_user = room_user; }

    bool authenticated() { return logged_in;  }
    void setAuthenticated(bool logged_in) { this->logged_in = logged_in; }

private:
    NetworkConnection *network_connection;
    EntityDetails *session_details;
    RoomUser *room_user;
    std::string unique_id;
    bool logged_in;
};