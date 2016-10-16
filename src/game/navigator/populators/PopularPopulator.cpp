#include "stdafx.h"

#include "game/navigator/populators/PopularPopulator.h"
#include "boot/Icarus.h"

std::vector<Room*> PopularPopulator::populate(bool room_limit, Player* player) {

    std::vector<Room*> rooms;

    for (auto room : *Icarus::getGame()->getRoomManager()->getRooms()) {
        if (room.second->getPlayers().size() > 0) {
            rooms.push_back(room.second);
        }
    }

    this->sort(rooms);
    return rooms;
}