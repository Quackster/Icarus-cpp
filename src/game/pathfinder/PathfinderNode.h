/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/room/Room.h"
#include "Position.h"

class PathfinderNode
{

public:
    PathfinderNode();
    PathfinderNode(Position position);
    ~PathfinderNode();

    std::shared_ptr<PathfinderNode> node;
    bool in_open;
    bool in_close;
    Position position;
    int cost;
};

