#include "stdafx.h"
#include "game/room/RoomData.h"

/*
    Constructor for RoomData
*/
RoomData::RoomData(int id,
    std::string name,
    char room_type,
    int owner_id,
    int group_id,
    std::string description,
    std::string password,
    int users_now,
    int users_max,
    std::string model,
    std::string wallpaper,
    std::string floor,
    std::string outside,
    std::vector<std::string> tags,
    int trade_state,
    int state,
    int score,
    int category,
    bool allow_pets,
    bool allow_pets_eat,
    bool allow_walkthrough,
    bool hide_wall,
    int floor_thickness,
    int wall_thickness,
    int chat_type,
    int chat_balloon,
    int chat_speed,
    int chat_max_distance,
    int chat_flood_protection,
    int who_can_mute,
    int who_can_kick,
    int who_can_ban) :
    id(id), 
    name(name), 
    owner_id(owner_id), 
    group_id(group_id), 
    description(description), 
    password(password), 
    users_now(users_now), 
    users_max(users_max), 
    model(model), 
    wallpaper(wallpaper), 
    floor(floor), 
    outside(outside), 
    tags(tags), 
    trade_state(trade_state), 
    state(state), 
    category(category), 
    allow_pets(allow_pets), 
    allow_pets_eat(allow_pets_eat), 
    allow_walkthrough(allow_walkthrough),
    hide_wall(hide_wall),
    floor_thickness(floor_thickness),
    wall_thickness(wall_thickness),
    chat_type(chat_type),
    chat_balloon(chat_balloon),
    chat_speed(chat_speed),
    chat_max_distance(chat_max_distance),
    chat_flood_protection(chat_flood_protection),
    who_can_mute(who_can_mute),
    who_can_kick(who_can_kick),
    who_can_ban(who_can_ban)
{
}

/*
    Deconstructor for RoomData
*/
RoomData::~RoomData()
{
}
