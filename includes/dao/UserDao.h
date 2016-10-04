#pragma once
#include <vector>
#include <string>

#include "mysql_connection.h"
#include "mysql.h"

#include "managers/session/Session.h"

using namespace std;

class UserDao
{

private:
    UserDao() { };

public:
    static bool authenticate(Session *session, string ssoTicket);

};

