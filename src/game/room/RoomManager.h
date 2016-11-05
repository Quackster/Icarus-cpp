/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <map>

#include "game/room/Room.h"
#include "game/room/model/RoomModel.h"

class RoomManager
{
public:
    RoomManager();
    ~RoomManager();

    void createPlayerRooms(int user_id);
    std::vector<Room*> getPlayerRooms(int user_id);

    RoomModel *getModel(std::string model_id);
    bool hasRoom(int room_id);
    Room *getRoom(int room_id);
    void addRoom(Room *room);
    void deleteRoom(int room_id);

    std::map<int, Room*> &getRooms() { return rooms; }
    std::vector<Room*> &getPublicRooms() { return public_rooms; }

private:
    std::map<int, Room*> rooms;
    std::vector<Room*> public_rooms;
    std::map<std::string, RoomModel*> models;
};

