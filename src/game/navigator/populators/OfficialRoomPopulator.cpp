#include "stdafx.h"

#include "OfficialRoomPopulator.h"
#include "boot/Icarus.h"

std::vector<Room*> OfficialRoomPopulator::populate(bool room_limit, Player* player) {

    std::vector<Room*> rooms;
    
    for (auto room : *Icarus::getGame()->getRoomManager()->getPublicRooms()) {

        rooms.push_back(room);
    }

    this->sort(rooms);

    return rooms;
}