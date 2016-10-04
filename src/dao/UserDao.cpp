#pragma once
#include "stdafx.h"
#include "dao/UserDao.h"
//#include "boot/Icarus.h"

void UserDao::authenticate(Session *session, string ssoTicket) {

    /*shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
    
    shared_ptr<sql::PreparedStatement> statement = shared_ptr<sql::PreparedStatement>(
        sql_connection->prepareStatement("SELECT id, username, rank, motto, figure, credits FROM users WHERE sso_ticket = ? LIMIT 1")
    );
    
    shared_ptr<sql::ResultSet> result_set = shared_ptr<sql::ResultSet>(statement->executeQuery());

    while (result_set->next()) {

        cout << result_set->getString("username") << endl;
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);*/
};

