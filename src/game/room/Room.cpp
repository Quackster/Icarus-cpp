/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include <cstring>

#include "game/room/Room.h"
#include "boot/Icarus.h"

#include "communication/outgoing/user/HotelViewMessageComposer.h"
#include "communication/outgoing/room/entry/RoomRatingMessageComposer.h"
#include "communication/outgoing/room/entry/RoomModelMessageComposer.h"
#include "communication/outgoing/room/entry/RoomSpacesMessageComposer.h"
#include "communication/outgoing/room/entry/RoomOwnerMessageComposer.h"
#include "communication/outgoing/room/entry/RightsLevelMessageComposer.h"
#include "communication/outgoing/room/entry/NoRightsMessageComposer.h"
#include "communication/outgoing/room/entry/PrepareRoomMessageComposer.h"


/*
    Constructor for rooms
*/
Room::Room(int room_id) :
    room_id(room_id),
    disposed(false),
    entities(new std::vector<Entity*>()),
    runnable(nullptr) {} //std::make_shared<RoomRunnable>(this)) { }

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
Enter room handler

@return none
*/
void Room::enter(Player* player) {

    this->disposed = false;

    /*if (this->getPlayers().size() == 0/* && this->runnable->isCancelled()) {
        //this->runnable->setCancelled(false);
        this->scheduleRunnable();
        //this->runnable->setCancelled(true);
    }*/

    // So we don't forget what room we entered 8-)
    player->getRoomUser()->setRoom(this);
    player->getRoomUser()->setLoadingRoom(true);
    player->getRoomUser()->setVirtualId(this->getData()->getVirtualId());

    player->send(RoomModelMessageComposer(this->getModel()->getName(), this->room_id));
    player->send(RoomRatingMessageComposer(room_data->getScore()));

    std::string floor = room_data->getFloor();
    std::string wall = room_data->getWallpaper();

    if (floor.length() > 0) {
        player->send(RoomSpacesMessageComposer("floor", floor));
    }

    if (wall.length() > 0) {
        player->send(RoomSpacesMessageComposer("wall", floor));
    }

    player->send(RoomSpacesMessageComposer("landscape", room_data->getOutside()));

    if (this->hasRights(player->getDetails()->getId(), true)) {
        player->getRoomUser()->setStatus("flatctrl", "useradmin");
        player->send(RoomOwnerMessageComposer());
        player->send(RightsLevelMessageComposer(4));
    }
    else if (this->hasRights(player->getDetails()->getId(), false)) {
        player->getRoomUser()->setStatus("flatctrl", "1");
        player->send(RightsLevelMessageComposer(1));
    }

    player->send(PrepareRoomMessageComposer(this->room_id));
}


/*
    Leave room, can send to hotel if option is given or dispose room

    @param player ptr
    @param hotel view
    @param dispose room
    @return none
*/
void Room::leave(Player* player, bool hotel_view, bool dispose) {

    if (hotel_view) {
        player->send(HotelViewMessageComposer());
    }

    if (this->hasEntity(player)) {

        // Remove entity from vector
        this->entities->erase(std::remove(this->entities->begin(), this->entities->end(), player), this->entities->end());

        // Reset room user
        player->getRoomUser()->reset();
    }

    if (dispose) {
        this->dispose();
    }
}

/*
    Serialise room data for response
    this is used in a number of places

    @param response
    @return none
*/
void Room::serialise(Response &response, bool enter_room) {

    response.writeInt(this->room_id);
    response.writeString(this->room_data->getName());
    response.writeInt(this->room_data->getOwnerId());
    response.writeString(this->room_data->getOwnerName()); // Owner name
    response.writeInt(this->room_data->getState());
    response.writeInt(this->getPlayers().size()); // Users now
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

    if (this->room_data->getThumbnail().length() > 0) {
        response_type += 1;
    }

    response.writeInt(response_type);

    if (this->room_data->getThumbnail().length() > 0) {
        response.writeString(this->room_data->getThumbnail());
    }
}

/*
    Returns whether or not the entity exists in the list of entities

    @param entity ptr
    @return boolean
*/
bool Room::hasEntity(Entity* entity) {
    return std::find(this->entities->begin(), this->entities->end(), entity) != this->entities->end();
}

/*
Gets list of players currently in the room

@return list of players
*/
std::vector<Player*> Room::getPlayers() {

    std::vector<Player*> players;

    for (auto entity : *this->entities) {
        if (entity->getEntityType() == PLAYER) {
            players.push_back(dynamic_cast<Player*>(entity));
        }
    }

    return players;
}


/*
    Dispose handler for Room

    @param (optional) force dispose of room
    @return none
*/
void Room::dispose(bool force_dispose) {

    bool reset = false;
    bool remove = false;

    if (force_dispose) {
        reset = true;
        remove = true;
        return;
    }

    bool empty_room = this->getPlayers().size() == 0;

    if (empty_room) {
        reset = true;
        if (this->room_data->isPrivate() && this->room_data->isOwnerOnline() == false) {
            remove = true;
        }
    }

    if (reset) {
        this->reset();
    }

    if (remove) {
        Icarus::getGame()->getRoomManager()->deleteRoom(this->room_id);
    }
}

/*
    Function to reset all room states to default
    used when there's no more users in the room or the room is getting deleted from memory

    @return none
*/
void Room::reset() {
    this->disposed = true;
    std::cout << "Room was reset" << std::endl;
}

/*
    Broadcast packet to entire room

    @param MessageComposer class
    @return none
*/
void Room::send(const MessageComposer &composer) {

    Response response = composer.compose();

    for (Player *player : this->getPlayers()) {
        player->getNetworkConnection()->send(response);
    }
}

/*
    Reschedule room runnable if it's not nullptr, it will not schedule if the room has been disposed

    @return none
*/
void Room::scheduleRunnable() {

    if (this->disposed) {
        return;
    }

    Icarus::getGame()->getGameScheduler()->schedule(this->runnable);
}

/*
    Deconstructor for rooms
*/
Room::~Room()
{
    std::cout << " Room ID " << this->room_id << " disposed." << std::endl;

    for (auto entity : *this->entities) {
        if (entity->getEntityType() != PLAYER) {
            delete entity; // Only delete non-playable entities
        }
    }

    delete room_data;
    delete entities;
}
