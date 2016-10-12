/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "game/room/Room.h"
#include "game/room/RoomUser.h"
#include "game/entities/Entity.h"
#include "communication/outgoing/room/UserStatusMessageComposer.h"

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
void RoomUser::updateStatus(std::string key, std::string value) {

    if (value.length() > 0) {
        this->statuses[key] = value;
    }
    else {
        this->statuses.erase(key);
    }

    this->updateStatus();
}

/*
    Updatest status, if value is empty, the status entry will be deleted

    @return none
*/
void RoomUser::updateStatus() {    
    this->room->send(UserStatusMessageComposer(this->entity));
}

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

    this->virtual_id = 0;
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
    bool is_walking = false;
    bool needs_update = false;
    bool is_loading_room = false;

}

/*
    Stop walking handler

    @param update user
*/
void RoomUser::stopWalking(bool needs_update) {

    if (this->statuses.count("mv") > 0) {
        this->statuses.erase("mv"); // remove status
    }

    this->needs_update = needs_update;
    this->path.clear();

    if (this->is_walking) {
        this->updateStatus();
    }

    this->is_walking = false;
}

/*
    Deconstructor for room user
*/
RoomUser::~RoomUser()
{
}
