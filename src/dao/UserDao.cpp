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
SessionDetails *UserDao::findUserByTicket(Session *session, std::string ssoTicket) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    SessionDetails *details = nullptr;

    try {

        std::shared_ptr<sql::Connection> sqlConnection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sqlConnection->prepareStatement("SELECT id, username, rank, motto, figure, credits FROM users WHERE sso_ticket = ? LIMIT 1")); {
            statement->setString(1, ssoTicket);
        }

        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (resultSet->next()) {

            /*
                This pointer gets deleted in the 'Session' deconstructor
            */
            details = new SessionDetails(
                resultSet->getInt("id"),
                resultSet->getString("username"),
                resultSet->getString("motto"),
                resultSet->getString("figure"),
                resultSet->getInt("rank"),
                resultSet->getInt("credits")
            );
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return details;
};

