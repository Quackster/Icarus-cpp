#include "stdafx.h"

#include "PopularPopulator.h"
#include "boot/Icarus.h"

std::vector<Room*> PopularPopulator::populate(bool room_limit, Player* player) {

    std::vector<Room*> rooms;

    for (auto kvp : *Icarus::getGame()->getRoomManager()->getRooms()) {

        Room *room = kvp.second;

        if (room->getPlayers().size() == 0) {
            continue;
        }

        if (!room->getData()->private_room) {
            continue;
        }

        if (room->getData()->room_state == ROOM_STATE_INVISIBLE) {
            if (!room->hasRights(player->getDetails()->id)) {
                continue;
            }
        }
        
        rooms.push_back(room);
    }

    this->sort(rooms);
    return rooms;
}