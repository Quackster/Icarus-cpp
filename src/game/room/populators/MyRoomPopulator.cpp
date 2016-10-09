#include "stdafx.h"

#include "game/navigator/populators/MyRoomPopulator.h"
#include "boot/Icarus.h"

std::vector<Room*> MyRoomPopulator::populate(bool room_limit, Player* player) {

    std::vector<Room*> rooms = Icarus::getGame()->getRoomManager()->getPlayerRooms(player->getDetails()->getId());
    this->sort(rooms);
    return rooms;
}