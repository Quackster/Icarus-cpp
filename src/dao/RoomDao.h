/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>
#include <string>

#include "game/room/Room.h"
#include "game/room/RoomManager.h"
#include "game/room/model/RoomModel.h"

#include "mysql_connection.h"
#include "mysql.h"

class RoomNewbie;
class RoomDao
{

private:
    RoomDao() { };

public:
    static std::map<std::string, RoomModel*> getModels();
	static std::vector<RoomNewbie*> RoomDao::getNewbieRoomSelection();
    static std::vector<int> getPlayerRooms(int user_id);
    static void addPublicRooms();
    static Room* getRoom(int room_id);
    static std::vector<Room*> getRooms(std::vector<int> room_ids);
    static std::vector<int> getRights(int room_id);
    static void deleteRoom(int room_id);
    static void updateRoom(int room_id, Room *room);
};

