#include "stdafx.h"

#include <cstring>

#include "game/room/Room.h"
#include "boot/Icarus.h"

/*
    Constructor for rooms
*/
Room::Room() { 
    this->entities = new std::vector<Entity*>();
}

/*
    Whether or not the user has room rights, has optional option for
    owner/staff check only
*/
bool Room::hasRights(int user_id, bool owner_check_only) {

    if (owner_check_only) {
        return this->room_data->getOwnerId() == user_id;
    }
    else {

        if (this->room_data->getOwnerId() == user_id) {
            return true;
        }
        else {
            return std::find(this->room_data->getUserRights().begin(), this->room_data->getUserRights().end(), user_id) != this->room_data->getUserRights().end();
        }
    }

}

/*
    Serialise room data for response
    this is used in a number of places

    @param response
    @return none
*/
void Room::serialise(Response &response, bool enter_room) {

    response.writeInt(this->room_data->getId());
    response.writeString(this->room_data->getName());
    response.writeInt(this->room_data->getOwnerId());
    response.writeString(this->room_data->getOwnerName()); // Owner name
    response.writeInt(this->room_data->getState());
    response.writeInt(0); // Users now
    response.writeInt(this->room_data->getUsersMax());
    response.writeString(this->room_data->getDescription());
    response.writeInt(this->room_data->getTradeState());
    response.writeInt(this->room_data->getScore());
    response.writeInt(0);
    response.writeInt(this->room_data->getCategory());
    response.writeInt(this->room_data->getTags().size());

    for (std::string tag : this->room_data->getTags()) {
        response.writeString(tag);
    }

    int response_type = 0;

    if (enter_room) {
        response_type = 32;
    }

    if (this->room_data->isPrivate()) {
        response_type += 8;
    }

    if (this->room_data->hasAllowPets()) {
        response_type += 16;
    }

    response.writeInt(response_type);
}

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
    std::cout << " Room ID " << this->room_data->getId() << " disposed." << std::endl;

    for (auto entity : *this->entities) {
        if (entity->getEntityType() != PLAYER) {
            delete entity; // Only delete non-playable entities
        }
    }

    this->entities->clear();

    delete room_data;
    delete entities;
}
