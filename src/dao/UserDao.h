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
#include "game/player/PlayerDetails.h"

class UserDao
{

private:
    UserDao() { };

public:
    static std::string getName(int user_id);
    static int getIdByUsername(std::string username);
    static PlayerDetails *findUserByTicket(Player *player, std::string sso_ticket);
    static std::shared_ptr<PlayerDetails>  getDetails(int user_id);
};

