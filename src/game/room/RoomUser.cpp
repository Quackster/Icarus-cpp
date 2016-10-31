/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "Room.h"
#include "game/entities/Entity.h"

#include "communication/outgoing/room/user/UserStatusMessageComposer.h"

/*
    Constructor for room user
*/
RoomUser::RoomUser(Entity *entity) : entity(entity) { 
    this->reset();
}

/*
    Updatest status, if value is empty, the status entry will be deleted

    @param status key
    @param status value
    @return none
*/
void RoomUser::setStatus(std::string key, std::string value, bool update) {

    if (value.length() > 0) {
        this->statuses[key] = value;
    }
    else {
        this->statuses.erase(key);
    }

    if (update) {
        //this->updateStatus();
		this->needs_update = true;
    }
}

/*
    Schedule player status to be updated for everyone in a room, loop happens every 0.5s
	this technically doesn't run instantly

    @return none
*/
void RoomUser::updateStatus() {    
    //this->room->send(UserStatusMessageComposer(this->entity));
	this->needs_update = true;
}
/*
    Sets rotation of user, optional to set head rotation too, and also optional to update player status

    @param body rotation
    @param head rotation
    @param bool update
    @return none
*/
void RoomUser::setRotation(int rotation, bool set_head_rotation, bool update) {
    this->rotation = rotation;
    
    if (set_head_rotation) {
        this->head_rotation = rotation;
    }
}

/*
    Restores all room user values (used when a user leaves the room)

    @return none
*/
void RoomUser::reset() {
    this->last_chat_id = 0;
    this->dance_id = 0;
    this->x = 0;
    this->y = 0;
    this->height = 0;
    this->goal_x = 0;
    this->goal_y = 0;
    this->rotation = 0;
    this->head_rotation = 0;
    this->statuses.clear();// = std::map<std::string, std::string>();
    this->path.clear();// = std::queue<Position>();
    this->room = nullptr;
    this->is_walking = false;
    this->is_loading_room = false;
    this->next = Position();

}

/*
    Stop walking handler, called when a user stops walking

	@return none
*/
void RoomUser::stopWalking() {

	Room *room = this->room;
	RoomModel *model = this->room->getModel();

	if (this->getPosition().getX() == model->getDoorX() && this->getPosition().getY() == model->getDoorY()) {
		room->leave(entity, true);
	}
}

/*
    Deconstructor for room user
*/
RoomUser::~RoomUser() { }
