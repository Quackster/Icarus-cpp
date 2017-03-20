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

#include "game/navigator/NavigatorTab.h"
#include "game/navigator/NavigatorCategory.h"

#include "mysql_connection.h"
#include "mysql.h"

class RoomData;
class Room;

enum NavigatorQuery {
    NAVIGATOR_FRIENDS_ROOMS
};

class NavigatorDao
{

private:
    NavigatorDao() { };

public:
    static int createRoom(std::string room_name, std::string description, std::string room_model, int owner_id, int category, int max_users, int trade_settings);
    static std::vector<NavigatorTab*> getTabsByChildId(int child_id);
    static std::vector<NavigatorCategory*> getCategories();
    static std::vector<Room*> getPreviewRooms(NavigatorQuery query, int user_id);
};

