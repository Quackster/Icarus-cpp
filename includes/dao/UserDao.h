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
    static PlayerDetails *findUserByTicket(Player *player, std::string sso_ticket);

};

