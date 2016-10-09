#pragma once
#include <vector>

#include "game/Player/Player.h"
#include "game/room/Room.h"

class RoomEntity
{

private:
    int virtual_id;
    int last_chat_id;
    int dance_id;

    int x;
    int y;
    double height;

    int goal_x;
    int goal_y;

    int rotation;
    int headRotation;

    std::map<std::string, std::string> statuses;
    //LinkedList<Point> path;

    Room room;

    bool is_walking;
    bool needs_wpdate;

public:

};