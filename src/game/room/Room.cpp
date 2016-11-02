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

#include "boot/Icarus.h"

#include "communication/outgoing/user/HotelViewMessageComposer.h"
#include "communication/outgoing/room/entry/RoomRatingMessageComposer.h"
#include "communication/outgoing/room/entry/RoomModelMessageComposer.h"
#include "communication/outgoing/room/entry/RoomSpacesMessageComposer.h"
#include "communication/outgoing/room/entry/HasOwnerRightsMessageComposer.h"
#include "communication/outgoing/room/entry/RightsLevelMessageComposer.h"
#include "communication/outgoing/room/entry/NoRightsMessageComposer.h"
#include "communication/outgoing/room/entry/PrepareRoomMessageComposer.h"
#include "communication/outgoing/room/user/RemoveUserMessageComposer.h"
#include "communication/outgoing/room/user/UserDisplayMessageComposer.h"
#include "communication/outgoing/room/user/UserStatusMessageComposer.h"

/*
    Constructor for rooms
*/
Room::Room(int room_id) :
    room_id(room_id),
    disposed(false),
    entities(new std::map<int, Entity*>()),
    runnable(nullptr) { } //std::make_shared<RoomRunnable>(this)) { }

/*
    Whether or not the user has room rights, has optional option for
    owner/staff check only
*/
bool Room::hasRights(const int user_id, const bool owner_check_only) {

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
void Room::enter(Player *player) {

    this->disposed = false;

    // So we don't forget what room we entered 8-)
    player->getRoomUser()->setRoom(this);
    player->getRoomUser()->setLoadingRoom(true);
    player->getRoomUser()->setVirtualId(this->getData()->getVirtualId());

    player->send(RoomModelMessageComposer(this->getModel()->getName(), this->room_id));
    player->send(RoomRatingMessageComposer(room_data->getScore()));

    int floor = stoi(room_data->getFloor());
    int wall = stoi(room_data->getWallpaper());

    if (floor > 0) {
        player->send(RoomSpacesMessageComposer("floor", std::to_string(floor)));
    }

    if (wall > 0) {
        player->send(RoomSpacesMessageComposer("wall", std::to_string(wall)));
    }

    player->send(RoomSpacesMessageComposer("landscape", room_data->getOutside()));

    if (this->hasRights(player->getDetails()->getId(), true)) {
        player->getRoomUser()->setStatus("flatctrl", "useradmin");
        
        player->send(RightsLevelMessageComposer(4));
        player->send(HasOwnerRightsMessageComposer());
    }
    else if (this->hasRights(player->getDetails()->getId(), false)) {
        player->getRoomUser()->setStatus("flatctrl", "1");

        player->send(RightsLevelMessageComposer(1));
    }

    if (!this->hasEntity(player)) {
        this->entities->insert(std::make_pair(player->getRoomUser()->getVirtualId(), player));
    }

    if (this->getPlayers().size() == 1) {
        if (this->runnable == nullptr) {
            this->runnable = std::make_shared<RoomRunnable>(this);
            this->scheduleRunnable();
        }
    }

    RoomModel *model = this->getModel();
    RoomUser *room_user = player->getRoomUser();

    room_user->setX(model->getDoorX());
    room_user->setY(model->getDoorY());
    room_user->setHeight(model->getDoorZ());
    room_user->setRotation(model->getDoorRotation(), true);

    this->send(UserDisplayMessageComposer(player));
    this->send(UserStatusMessageComposer(player));

    player->send(PrepareRoomMessageComposer(this->room_id));
}


/*
    Leave room, can send to hotel if option is given or dispose room

    @param player ptr
    @param hotel view
    @param dispose room
    @return none
*/
void Room::leave(Entity *entity, const bool hotel_view, const bool dispose) {

    if (this->hasEntity(entity)) {

        // Remove entity from vector
        this->entities->erase(entity->getRoomUser()->getVirtualId());

        // Remove entity from room
        this->send(RemoveUserMessageComposer(entity->getRoomUser()->getVirtualId()));


        if (entity->getEntityType() == PLAYER) {
            if (hotel_view) {

                Player *player = dynamic_cast<Player*>(entity);

                player->send(HotelViewMessageComposer());
                player->getMessenger()->sendStatus(false);
            }
        }

        // Reset room user
        entity->getRoomUser()->reset();
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
void Room::serialise(Response &response, const bool enter_room) {

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
bool Room::hasEntity(Entity *entity) {
    return this->entities->count(entity->getRoomUser()->getVirtualId()) > 0;
}

/*
Gets list of players currently in the room

@return list of players
*/
const std::vector<Player*> Room::getPlayers() {

    std::vector<Player*> players;

    for (auto kvp : *this->entities) {

        Entity *entity = kvp.second;

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
void Room::dispose(const bool force_dispose) {

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
        if (this->room_data->isOwnerOnline() == false) {
            if (this->room_data->isPrivate()) {
                remove = true;
            }
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

    for (auto kvp : *this->entities) {

        Entity *entity = kvp.second;

        if (entity->getEntityType() != PLAYER) {
            delete entity; // Only delete non-playable entities
        }
    }

    delete room_data;
    this->room_data = nullptr;

    delete entities;
    this->entities = nullptr;
}
