/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>
#include <vector>

#include "model/RoomModel.h"

class Room;

class RoomState {
    
public:
    static const int OPEN = 0;
    static const int INVISIBLE = 3;
    static const int DOORBELL = 1;
    static const int PASSWORD = 2;
};

struct RoomData {
    int id;
    std::string name;
    char room_type;
    std::string thumbnail;
    int owner_id;
    Player *owner;
    std::string owner_name;
    int group_id;
    std::string description;
    std::string password;
    int users_now = 0;
    int users_max;
    RoomModel *model;
    std::string wallpaper;
    std::string floor;
    std::string outside;
    std::vector<std::string> tags;
    int trade_state;
    int state;
    int score;
    int category;
    bool allow_pets;
    bool allow_pets_eat;
    bool allow_walkthrough;
    int floor_thickness;
    int wall_thickness;
    bool hide_wall;
    int wall_height = -1;
    int chat_mode;
    int chat_size;
    int chat_speed;
    int chat_flood;
    int chat_distance;
    int who_can_mute;
    int who_can_kick;
    int who_can_ban;
    int virtual_id = 0;
    std::vector<int> user_rights;
    bool private_room = true;
};

