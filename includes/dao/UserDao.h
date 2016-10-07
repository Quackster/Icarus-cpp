#pragma once
#include <vector>
#include <string>

#include "mysql_connection.h"
#include "mysql.h"

#include "game/session/Session.h"

class UserDao
{

private:
    UserDao() { };

public:
    static SessionDetails *findUserByTicket(Session *session, std::string ssoTicket);

};

