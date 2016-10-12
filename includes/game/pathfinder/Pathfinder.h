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
#include "game/pathfinder/Position.h"
#include "game/pathfinder/PathfinderNode.h"

class Pathfinder
{
public:
    ~Pathfinder();


    static std::vector<Position> makePath(Position start, Position end, Room *room);
    static std::shared_ptr<PathfinderNode> makePathReversed(Position start, Position end, Room *room);
    static bool isValidStep(Room *room, Position current, Position tmp, bool is_final_move);

    static std::vector<Position> getPoints() {

        std::vector<Position> points;

        points.push_back(Position(0, -1));
        points.push_back(Position(0, 1));
        points.push_back(Position(1, 0));
        points.push_back(Position(-1, 0));
        points.push_back(Position(1, -1));
        points.push_back(Position(-1, 1));
        points.push_back(Position(1, 1));
        points.push_back(Position(-1, -1));

        return points;
    }
};

