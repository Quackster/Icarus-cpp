#include "stdafx.h"

#include "game/room/populators/MyRoomPopulator.h"
#include "boot/Icarus.h"

std::vector<Room*> MyRoomPopulator::populate(bool room_limit, Session* session) {

    std::vector<Room*> rooms = Icarus::getGame()->getRoomManager()->getPlayerRooms(session->getDetails()->getId());

    return rooms;
}