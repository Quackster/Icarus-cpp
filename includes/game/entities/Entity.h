/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/room/RoomUser.h"

#include "game/entities/EntityDetails.h"
#include "game/entities/EntityType.h"

class Entity
{

public:
    ~Entity() { }

    virtual EntityDetails *getDetails() = 0;
    virtual void setDetails(EntityDetails *details) = 0;

    virtual RoomUser *getRoomUser() = 0;
    virtual void setRoomUser(RoomUser *room_user) = 0;

    virtual EntityType getEntityType() = 0;

};
