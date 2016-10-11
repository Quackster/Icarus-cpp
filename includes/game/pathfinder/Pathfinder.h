#pragma once
#include <queue>

#include "game/pathfinder/Position.h"
#include "game/room/RoomUser.h"

class RoomUser;
class Pathfinder
{
public:
    Pathfinder();
    Pathfinder(RoomUser *room_user);
    ~Pathfinder();

private:
    RoomUser *room_user;
};

