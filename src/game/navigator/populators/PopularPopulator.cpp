#include "stdafx.h"

#include "game/navigator/populators/PopularPopulator.h"
#include "boot/Icarus.h"

std::vector<Room*> PopularPopulator::populate(bool room_limit, Player* player) {

    std::vector<Room*> rooms;

    for (auto room : *Icarus::getGame()->getRoomManager()->getRooms()) {

        printf("player size: %i\n", room.second->getPlayers().size());

        if (room.second->getPlayers().size() > 0 && room.second->getData()->isPrivate()) {
            rooms.push_back(room.second);
        }
    }

    this->sort(rooms);
    return rooms;
}