#include "stdafx.h"

#include <vector>

#include "boot/Icarus.h"
#include "game/navigator/populators/DefaultPopulator.h"

std::vector<Room*> DefaultPopulator::populate(bool room_limit, Player* player) {

    std::vector<Room*> rooms;
    
    for (auto room : *Icarus::getGame()->getRoomManager()->getRooms()) {

        if (room.second->getPlayers().size() > 0) {

            rooms.push_back(room.second);
        }
    }

    this->sort(rooms);

    return rooms;
}