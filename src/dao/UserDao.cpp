#pragma once
#include "stdafx.h"
#include "dao/UserDao.h"
#include "dao/MySQLDao.h"
#include "boot/Icarus.h"

/*
    Returns true or false if a user exists by sso ticket

    @param sso ticket
    @return bool
*/
bool UserDao::exists(std::string sso_ticket) {

    bool output = false;
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {
        std::shared_ptr<sql::Connection> sqlConnection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sqlConnection->prepareStatement("SELECT id FROM users WHERE sso_ticket = ?")); {
            statement->setString(1, sso_ticket);
        }

        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery());
        output = resultSet->next();
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return output;
}

/*
    Returns username by given user id

    @param user id
    @return std::string username
*/

std::string UserDao::getName(int user_id) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    std::string username;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT username FROM users WHERE id = ? LIMIT 1")); {
            statement->setInt(1, user_id);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {
            username = result_set->getString("username");
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return username;
};

int UserDao::getIdByUsername(std::string username) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    int user_id = 0;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id FROM users WHERE username = ? LIMIT 1")); {
            statement->setString(1, username);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {
            user_id = result_set->getInt("id");
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return user_id;
}


/*
    Finds session data based on their SSO ticket.

    @param Session pointer
    @param SSO ticket requested

    @return SessionData ptr or nullptr (check if this returns nullptr for failure of finding user)
*/
PlayerDetails *UserDao::findUserByTicket(Player *player, std::string ssoTicket) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id, username, rank, mission, figure, credits FROM users WHERE sso_ticket = ? LIMIT 1")); {
            statement->setString(1, ssoTicket);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {

            /*
                This pointer gets deleted in the 'Session' deconstructor
            */
            return new PlayerDetails(
                result_set->getInt("id"),
                result_set->getString("username"),
                result_set->getString("mission"),
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

    return nullptr;
}

/*
    Finds session data based on their user id, returns a smart pointer since we still want to use null, but don't need to 
    worry about the lifetime of the object.

    @param user id

    @return SessionData ptr or nullptr (check if this returns nullptr for failure of finding user)
*/
std::shared_ptr<PlayerDetails> UserDao::getDetails(int user_id) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    std::shared_ptr<PlayerDetails> details = nullptr;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id, username, rank, mission, figure, credits FROM users WHERE id = ? LIMIT 1")); {
            statement->setInt(1, user_id);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {

            /*
            This pointer gets deleted in the 'Session' deconstructor
            */
            details = std::make_shared<PlayerDetails>(
                result_set->getInt("id"),
                result_set->getString("username"),
                result_set->getString("mission"),
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

