#include "stdafx.h"

#include <deque>

#include "game/room/Room.h"
#include "game/room/model/RoomModel.h"
#include "game/pathfinder/Pathfinder.h"

Pathfinder::Pathfinder() :
    room_user(nullptr) { 
}


Pathfinder::Pathfinder(RoomUser *room_user) :
    room_user(room_user) { 
}

Pathfinder::~Pathfinder() {
    delete this->room_user;
}