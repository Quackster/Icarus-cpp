#include "stdafx.h"

#include <cstring>

#include "game/room/Room.h"
#include "boot/Icarus.h"
#include "communication/outgoing/user/HotelViewMessageComposer.h"

#include "communication/outgoing/room/UserDisplayMessageComposer.h"
#include "communication/outgoing/room/UserStatusMessageComposer.h"

/*
    Constructor for rooms
*/
Room::Room() : disposed(false), entities(new std::vector<Entity*>()), room_runnable(nullptr) { }

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

  if (this->entities->size() == 0) {
      this->room_runnable = new RoomRunnable(this);
      this->scheduleRunnable();
    }

    player->getRoomUser()->setLoadingRoom(false);

    RoomModel *model = this->room_data->getModel();
    RoomUser *room_user = player->getRoomUser();

    room_user->setX(model->getDoorX());
    room_user->setY(model->getDoorY());
    room_user->setHeight(model->getDoorZ());
    room_user->setRotation(model->getDoorRotation(), true);

    this->send(UserDisplayMessageComposer(player));
    this->send(UserStatusMessageComposer(player));

    player->send(UserDisplayMessageComposer(*this->entities));
    player->send(UserStatusMessageComposer(*this->entities));

    if (!this->hasEntity(player)) {
        this->entities->push_back(player);
    }
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

    response.writeInt(this->room_data->getId());
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

    response.writeInt(response_type);
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

    if (force_dispose) {
        this->reset();
        Icarus::getGame()->getRoomManager()->deleteRoom(this->room_data->getId());
        return;
    }

    bool empty_room = this->getPlayers().size() == 0;

    if (empty_room) {
        this->reset();
        if (this->room_data->isOwnerOnline() == false && empty_room) {
            Icarus::getGame()->getRoomManager()->deleteRoom(this->room_data->getId());
        }
    }
}

/*
    Function to reset all room states to default
    used when there's no more users in the room or the room is getting deleted from memory

    @return none
*/
void Room::reset() {

    if (this->room_runnable != nullptr) {
        delete this->room_runnable;
        this->room_runnable = nullptr;
    }

    this->disposed = true;
}

/*
    Broadcast packet to entire room

    @param MessageComposer class
    @return none
*/
void Room::send(MessageComposer &composer) {

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

    if (this->room_runnable != nullptr) {
        Icarus::getGame()->getGameScheduler()->schedule(this->room_runnable);
    }
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

    if (room_runnable != nullptr) {
        delete room_runnable;
    }

    delete room_data;
    delete entities;
}
