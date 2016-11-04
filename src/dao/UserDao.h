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

#include "mysql_connection.h"
#include "mysql.h"

#include "game/player/Player.h"

class UserDao
{

private:
    UserDao() { };

public:

    static bool exists(std::string sso_ticket);
    static std::string getName(int user_id);
    static int getIdByUsername(std::string username);
    static EntityDetails *findUserByTicket(Player *player, std::string sso_ticket);
    static std::shared_ptr<EntityDetails>  getDetails(int user_id);
    static void updateUser(int user_id, EntityDetails *details);
};

