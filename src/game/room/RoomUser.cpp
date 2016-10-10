#include "stdafx.h"

#include "game/room/RoomUser.h"

/*
    Constructor for room user
*/
RoomUser::RoomUser() { 
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
    this->room = nullptr;
    bool is_walking = false;
    bool needs_update = false;
    bool is_loading_room = false;

}

/*
    Deconstructor for room user
*/
RoomUser::~RoomUser()
{
}
