#include "stdafx.h"

#include "game/room/Room.h"
#include "boot/Icarus.h"

/*
    Constructor for rooms
*/
Room::Room() { }

/*
    Dispose handler for Room

    @param (optional) force dispose of room
    @return none
*/
void Room::dispose(bool force_dispose) {

    if (force_dispose) {

        Icarus::getGame()->getRoomManager()->deleteRoom(this->room_data->getId());
    }

    // if room users is 0
    // 
    // reset state
    //
    //    if owner not online
    //        Icarus::getGame()->getRoomManager()->deleteRoom(this->room_data->getId());

    Icarus::getGame()->getRoomManager()->deleteRoom(this->room_data->getId());
}

/*
    Deconstructor for rooms
*/
Room::~Room()
{
    std::cout << "Room ID " << this->room_data->getId() << " disposed." << std::endl;
    delete room_data;
}
