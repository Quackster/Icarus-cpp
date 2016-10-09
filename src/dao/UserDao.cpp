#pragma once
#include "stdafx.h"
#include "dao/UserDao.h"
#include "boot/Icarus.h"

/*
    Finds session data based on their SSO ticket.

    @param Session pointer
    @param SSO ticket requested

    @return SessionData ptr or nullptr (check if this returns nullptr for failure of finding user)
*/
PlayerDetails *UserDao::findUserByTicket(Player *player, std::string ssoTicket) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    PlayerDetails *details = nullptr;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id, username, rank, motto, figure, credits FROM users WHERE sso_ticket = ? LIMIT 1")); {
            statement->setString(1, ssoTicket);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {

            /*
                This pointer gets deleted in the 'Session' deconstructor
            */
            details = new PlayerDetails(
                result_set->getInt("id"),
                result_set->getString("username"),
                result_set->getString("motto"),
                result_set->getString("figure"),
                result_set->getInt("rank"),
                result_set->getInt("credits")
            );
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return details;
};

