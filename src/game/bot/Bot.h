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

class Bot : public Entity {

public:
    Bot(EntityDetails *details);
    ~Bot();

    RoomUser *getRoomUser() { return room_user; }
    EntityDetails *getDetails() { return this->details; }

    void setDetails(EntityDetails *details) { this->details = details; };
    void setRoomUser(RoomUser *room_user) { this->room_user = room_user; };

    EntityType getEntityType() { EntityType type = BOT; return type; }
    
    

private:
    EntityDetails *details = nullptr;
    RoomUser *room_user = nullptr;
};