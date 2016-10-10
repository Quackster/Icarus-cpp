#include "stdafx.h"

#include "game/room/RoomUser.h"

/*
    Constructor for room user
*/
RoomUser::RoomUser() { 
    this->reset();
}

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
