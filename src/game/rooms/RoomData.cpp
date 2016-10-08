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
    bool allow_walkthrough) :
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
    allow_walkthrough(allow_walkthrough)
{
}

/*
    Deconstructor for RoomData
*/
RoomData::~RoomData()
{
}
