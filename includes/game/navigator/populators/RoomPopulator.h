#pragma once
#include <vector>

#include "game/player/Player.h"
#include "game/room/Room.h"

struct PopulationSorter {
    inline bool operator() (Room* struct1, Room* struct2) {
        return struct1->getPlayers().size() > struct2->getPlayers().size();//(struct1.key < struct2.key);
    }
};

class RoomPopulator
{

public:
    virtual ~RoomPopulator() {}
    virtual std::vector<Room*> populate(bool room_limit, Player *player) = 0;
    
    void sort(std::vector<Room*> &rooms) {
        std::sort(rooms.begin(), rooms.end(), PopulationSorter());
    }
};