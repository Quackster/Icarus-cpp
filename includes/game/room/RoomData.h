#pragma once
#include <string>
#include <vector>

class RoomData
{
public:
    RoomData(int id,
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
        int who_can_ban);

    int getId() { return id; }
    std::string getName() { return name; }
    bool isPrivate() { return room_type == 0; }
    int getOwnerId() { return owner_id; }

    ~RoomData();

private:
    int id;
    std::string name;
    char room_type;
    int owner_id;
    int group_id;
    std::string description;
    std::string password;
    int users_now;
    int users_max;
    std::string model;
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
    int chat_type;
    int chat_balloon;
    int chat_speed;
    int chat_max_distance;
    int chat_flood_protection;
    int who_can_mute;
    int who_can_kick;
    int who_can_ban;
};

