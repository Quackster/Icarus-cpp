/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>

#include "RoomPopulator.h"

class DefaultPopulator : public RoomPopulator {

public:
    DefaultPopulator() { }
    std::vector<Room*> populate(bool room_limit, Player* player);
};