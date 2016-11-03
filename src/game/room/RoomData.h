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
class RoomData
{
public:
    RoomData(int id,
        std::string name,
        char room_type,
        std::string thumbnail,
        int owner_id,
        std::string owner_name,
        int group_id,
        std::string description,
        std::string password,
        int users_max,
        RoomModel *model,
        //std::string model,
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
        int chat_mode,
        int chat_size,
        int chat_speed,
        int chat_flood,
        int chat_distance,
        int who_can_mute,
        int who_can_kick,
        int who_can_ban,
        std::vector<int> user_rights);

    int &getId() { return id; }
    std::string &getName() { return name; }
    bool isPrivate() { return room_type == 0; }
    std::string &getThumbnail() { return thumbnail;  }
    int &getOwnerId() { return owner_id; }
    std::string &getOwnerName() { return owner_name; }
    Player *getOwner() { return owner; }
    bool isOwnerOnline();
    int &getGroupId() { return group_id; }
    std::string &getDescription() { return description; }
    std::string &getPassword() { return password; }
    int &getUsersMax() { return users_max; }
    RoomModel *getModel() { return this->model; }
    std::string &getWallpaper() { return wallpaper; }
    std::string &getFloor() { return floor; }
    std::string &getOutside() { return outside; }
    std::vector<std::string> &getTags() { return tags; }
    int &getTradeState() { return trade_state; }
    int &getState() { return state; }
    int &getScore() { return score; }
    int &getCategory() { return category; }
    bool &hasAllowPets() { return allow_pets; }
    bool &hasAllowPetsEat() { return allow_pets_eat; }
    bool &hasAllowWalkthrough() { return allow_walkthrough; }
    bool &hasHideWall() { return hide_wall; }
    int &getFloorThickness() { return floor_thickness; }
    int &getWallThickness() { return wall_thickness; }
    int getWallHeight() { return -1; }
    int &getWhoCanMute() { return who_can_mute; }
    int &getWhoCanKick() { return who_can_kick; }
    int &getWhoCanBan() { return who_can_ban; }
    int getChatMode() { return chat_mode; }
    int getChatSize() { return chat_size; }
    int getChatSpeed() { return chat_speed; }
    int getChatFlood() { return chat_flood; }
    int getChatDistance() { return chat_distance; }
    int getVirtualId() { this->virtual_id = this->virtual_id + 1; return virtual_id; }

    void setName(std::string name) { this->name = name; }
    void setName(std::string description) { this->description = description; }
    /*
    
    std::string room_name = request.readString();
        std::string description = request.readString();
        int access_type = request.readInt();
        int max_users = request.readInt();
        int category_id = request.readInt();
        int tag_size = request.readInt();

        std::vector<std::string> tags;

        for (int i = 0; i < tag_size; i++) {
            tags.push_back(request.readString());
        }

        int trade_settings = request.readInt();
        int allow_pets = request.readInt();
        int allow_pets_eat = request.readInt();
        int allow_walkthrough = request.readInt();
        int hide_wall = request.readInt();
        int wall_thickness = request.readInt();
        int floor_thickness = request.readInt();
        int who_can_mute = request.readInt();
        int who_can_kick = request.readInt();
        int who_can_ban = request.readInt();
        int chat_mode = request.readInt();
        int chat_size = request.readInt();
        int chat_speed = request.readInt();
        int chat_distance = request.readInt();
        int chat_flood = request.readInt();
        int trade_settings = request.readInt();
    */


    std::vector<int> &getUserRights() { return user_rights; }
    ~RoomData();

private:
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
    int users_max;
    //std::string model;
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
    int chat_mode;
    int chat_size;
    int chat_speed;
    int chat_flood;
    int chat_distance;
    int who_can_mute;
    int who_can_kick;
    int who_can_ban;
    int virtual_id;

    //bool moonwalk = true;

    std::vector<int> user_rights;
};

