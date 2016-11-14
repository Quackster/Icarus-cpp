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

#include "dao/RoomDao.h"

#include "game/bot/Bot.h"

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
Room::Room(int room_id, RoomData *room_data) :
    id(room_id),
    disposed(false),
    //entities(new std::map<int, Entity*>()),
    runnable(nullptr),
    room_data(room_data) { 



} //std::make_shared<RoomRunnable>(this)) { }

/*
    Whether or not the user has room rights, has optional option for
    owner/staff check only
*/
bool Room::hasRights(const int user_id, const bool owner_check_only) {

    if (owner_check_only) {
        return this->room_data->owner_id == user_id;
    }
    else {

        if (this->room_data->owner_id != user_id) {

            // Check to see if user id is located in room_data->user_rights vector
            return std::find(this->room_data->user_rights.begin(), this->room_data->user_rights.end(), user_id) != this->room_data->user_rights.end();

        }
        else {
            return true;
        }
    }
}

/*
Enter room handler

@return none
*/
void Room::enter(Entity *entity) {

    RoomModel *model = this->getModel();
    RoomUser *room_user = entity->getRoomUser();

    room_user->position.x = model->getDoorX();
    room_user->position.y = model->getDoorY();
    room_user->height = model->getDoorZ();
    room_user->setRotation(model->getDoorRotation(), true);
    room_user->setRoom(this);

    room_user->virtual_id = this->getData()->virtual_id;
    this->updateVirtualId();

    if (!this->hasEntity(entity)) {
        this->entities.insert(std::make_pair(room_user->virtual_id, entity));
    }

    if (entity->getEntityType() != PLAYER) {
        return;
    }

    Player *player = dynamic_cast<Player*>(entity);

    this->disposed = false;
    room_user->is_loading_room = true;

    player->send(RoomModelMessageComposer(this->getModel()->getName(), this->id));
    player->send(RoomRatingMessageComposer(room_data->score));

    int floor = stoi(room_data->floor);
    int wall = stoi(room_data->wallpaper);

    if (floor > 0) {
        player->send(RoomSpacesMessageComposer("floor", std::to_string(floor)));
    }

    if (wall > 0) {
        player->send(RoomSpacesMessageComposer("wall", std::to_string(wall)));
    }

    player->send(RoomSpacesMessageComposer("landscape", room_data->outside));

    if (this->hasRights(player->getDetails()->id, true)) {
        player->getRoomUser()->setStatus("flatctrl", "useradmin");

        player->send(RightsLevelMessageComposer(4));
        player->send(HasOwnerRightsMessageComposer());
    }
    else if (this->hasRights(player->getDetails()->id, false)) {
        player->getRoomUser()->setStatus("flatctrl", "1");

        player->send(RightsLevelMessageComposer(1));
    }

    if (this->getPlayers().size() == 1) {

        this->load();

        if (this->runnable == nullptr) {
            this->runnable = std::make_shared<RoomRunnable>(this);
            this->scheduleRunnable();
        }
    }

    this->send(UserDisplayMessageComposer(player));
    this->send(UserStatusMessageComposer(player));

    player->send(PrepareRoomMessageComposer(this->id));
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
        this->entities.erase(entity->getRoomUser()->virtual_id);

        // Remove entity from room
        this->send(RemoveUserMessageComposer(entity->getRoomUser()->virtual_id));


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
    Kick all users in room

    @return none
*/
void Room::kickPlayers() {

    for (auto player : this->getPlayers()) {

        if (player->getRoomUser()->in_room) {
            player->getRoomUser()->getRoom()->leave(player, true);
        }
    }
}

/*
    Serialise room data for response
    this is used in a number of places

    @param response
    @return none
*/
void Room::serialise(Response &response, const bool enter_room) {

    response.writeInt(this->id);
    response.writeString(this->room_data->name);
    response.writeInt(this->room_data->owner);
    response.writeString(this->room_data->owner_name); // Owner name
    response.writeInt(this->room_data->state);
    response.writeInt(this->getPlayers().size()); // Users now
    response.writeInt(this->room_data->users_max);
    response.writeString(this->room_data->description);
    response.writeInt(this->room_data->trade_state);
    response.writeInt(this->room_data->score);
    response.writeInt(0);
    response.writeInt(this->room_data->category);
    response.writeInt(this->room_data->tags.size());

    for (std::string tag : this->room_data->tags) {
        response.writeString(tag);
    }

    int response_type = 0;

    if (enter_room) {
        response_type = 32;
    }

    if (this->room_data->private_room) {
        response_type += 8;
    }

    if (this->room_data->allow_pets) {
        response_type += 16;
    }

    if (this->room_data->thumbnail.length() > 0) {
        response_type += 1;
    }

    response.writeInt(response_type);

    if (this->room_data->thumbnail.length() > 0) {
        response.writeString(this->room_data->thumbnail);
    }
}

/*
    Returns whether or not the entity exists in the list of entities

    @param entity ptr
    @return boolean
*/
bool Room::hasEntity(Entity *entity) {
    return this->entities.count(entity->getRoomUser()->virtual_id) > 0;
}

/*
Gets list of players currently in the room

@return list of players
*/
const std::vector<Player*> Room::getPlayers() {

    std::vector<Player*> players;

    for (auto kvp : this->entities) {

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
    }
    else {

        bool empty_room = this->getPlayers().size() == 0;

        if (empty_room) {
            reset = true;
            if (this->isOwnerOnline() == false) {
                if (this->room_data->private_room) {
                    remove = true;
                }
            }
        }
    }

    if (reset) {
        this->unload();
    }

    if (remove) {
        Icarus::getGame()->getRoomManager()->deleteRoom(this->id);
    }
}

/*
    Function to load all bots and other pieces of data such as furniture

    @return none
*/
void Room::load() {

    if (Icarus::getLogConfiguration()->getBool("log.room.loaded")) {
        cout << " [ROOM] Room ID " << this->id << " loaded" << endl;
    }

    if (this->id == 5) {

        for (int i = 0; i < 20; i++) {
            EntityDetails *details = new EntityDetails();
            details->username = "TheBestBot-" + std::to_string(Icarus::getRandomNumber(0, 200));
            details->figure = "hr-893-54.hd-185-26.ch-265-91.lg-280-76.sh-300-83.ha-1013-100.he-1603-71.ea-1406-.fa-1205-75.ca-1809-";
            details->motto = "i love u";
            details->id = Icarus::getRandomNumber(0, 200);

            Bot *bot = new Bot(details);
            this->enter(bot);
        }

    }

}

/*
    Function to reset all room states to default
    used when there's no more users in the room or the room is getting deleted from memory

    @return none
*/
void Room::unload() {
    this->disposed = true;

    if (Icarus::getLogConfiguration()->getBool("log.room.unloaded")) {
        cout << " [ROOM] Room ID " << this->id << " unloaded" << endl;
    }

    for (auto kvp : this->entities) {
        Entity *entity = kvp.second;

        if (entity->getEntityType() == BOT) {
            delete entity; // Only delete non-playable entities
        }
    }

    this->entities.clear();

}

/*
    Broadcast packet to entire room

    @param MessageComposer class
    @return none
*/
void Room::send(const MessageComposer &composer, const bool users_with_rights) {

    Response response = composer.compose();

    if (!users_with_rights) {

        for (Player *player : this->getPlayers()) {
            player->getNetworkConnection()->send(response);
        }
    }
    else {

        for (int user_id : this->room_data->user_rights) {

            Player *player = Icarus::getPlayerManager()->getPlayerById(user_id);

            if (player != nullptr) {
                player->getNetworkConnection()->send(response);
            }
        }
    }
}

/*
    True or false whether or not the owner is online

    @return boolean
*/

bool Room::isOwnerOnline() {
    this->room_data->owner = Icarus::getPlayerManager()->getPlayerById(this->room_data->owner_id);
    return this->room_data->owner != nullptr;
}

/*
    Updates virtual id

    @return none
*/
void Room::updateVirtualId() {
    this->room_data->virtual_id = this->room_data->virtual_id + 1;
}

/*
    Save room data

    @return none
*/
void Room::save() {
    RoomDao::updateRoom(this->id, this);
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
Room::~Room() {

    delete room_data;
    this->room_data = nullptr;

   // delete entities;
    //this->entities = nullptr;
}
