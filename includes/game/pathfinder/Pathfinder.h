#pragma once
#include "game/room/Room.h"
#include "game/pathfinder/Position.h"
#include "game/pathfinder/PathfinderNode.h"

class Pathfinder
{
public:
    ~Pathfinder();


    static std::vector<Position> makePath(Position start, Position end, Room *room);
    static PathfinderNode *makePathReversed(Position start, Position end, Room *room);
    static bool isValidStep(Room *room, Position current, Position tmp, bool is_final_move);

    static Position* getPoints() {

        static Position POINTS[8] = {
            Position(0, -1),
            Position(0, 1),
            Position(1, 0),
            Position(-1, 0),
            Position(1, -1),
            Position(-1, 1),
            Position(1, 1),
            Position(-1, -1)
        };

        return POINTS;
    }
};

