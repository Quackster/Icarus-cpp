#pragma once
#include <vector>

#include "game/navigator/populators/RoomPopulator.h"

class DefaultPopulator : public RoomPopulator {

public:
    DefaultPopulator() { }
    std::vector<Room*> populate(bool room_limit, Player* player);
};