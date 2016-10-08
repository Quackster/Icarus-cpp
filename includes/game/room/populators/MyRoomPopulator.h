#pragma once
#include <vector>

#include "game/room/populators/RoomPopulator.h"

class MyRoomPopulator : public RoomPopulator {

public:
    MyRoomPopulator() { }
    std::vector<Room*> populate(bool room_limit, Session* session);
};