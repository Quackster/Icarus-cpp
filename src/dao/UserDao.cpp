#pragma once
#include "stdafx.h"
#include "dao/UserDao.h"
#include "boot/Icarus.h"

/*
    Authenticates user by their SSO ticket, will also fill their data if they are found.

    @param Session pointer
    @param SSO ticket requested

    @return whether or not their user was found
*/
SessionDetails *UserDao::findUserByTicket(Session *session, string ssoTicket) {

    shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        shared_ptr<sql::Connection> sqlConnection = connection->sql_connection;
        shared_ptr<sql::PreparedStatement> statement = shared_ptr<sql::PreparedStatement>(sqlConnection->prepareStatement("SELECT id, username, rank, motto, figure, credits FROM users WHERE sso_ticket = ? LIMIT 1")); {
            statement->setString(1, ssoTicket);
        }

        shared_ptr<sql::ResultSet> resultSet = shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (resultSet->next()) {

            SessionDetails *details = new SessionDetails(
                resultSet->getInt("id"),
                resultSet->getString("username"),
                resultSet->getString("motto"),
                resultSet->getString("figure"),
                resultSet->getInt("rank"),
                resultSet->getInt("credits")
            );

            return details;
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return nullptr;
};

