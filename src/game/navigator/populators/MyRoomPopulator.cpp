#include "stdafx.h"

#include "MyRoomPopulator.h"
#include "boot/Icarus.h"

std::vector<Room*> MyRoomPopulator::populate(bool room_limit, Player* player) {

    std::vector<Room*> rooms = Icarus::getGame()->getRoomManager()->getPlayerRooms(player->getDetails()->id);
    this->sort(rooms);
    return rooms;
}