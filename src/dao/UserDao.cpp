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
        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id FROM users WHERE sso_ticket = ?")); {
            statement->setString(1, sso_ticket);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());
        output = result_set->next();
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);

        std::string error_message = e.what();

        // If MySQL has gone away, we will try again since the database manager would have already reconnected
        if (error_message.find("has gone away") != std::string::npos) {
            return exists(sso_ticket);
        }

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

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
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

/*
    Returns a players user id by given username, this performs a database lookup

    @param username of user
    @return 0 if not found, more than 0 if found
*/
int UserDao::getIdByUsername(std::string username) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    int user_id = 0;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
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
EntityDetails *UserDao::findUserByTicket(Player *player, std::string sso_ticket) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    EntityDetails *details = nullptr;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT * FROM users WHERE sso_ticket = ? LIMIT 1")); {
            statement->setString(1, sso_ticket);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {

            /*
                This pointer gets deleted in the 'Session' deconstructor
            */
            details = new EntityDetails(player);

            details->id = result_set->getInt("id");
            details->username = result_set->getString("username");
            details->motto = result_set->getString("mission");
            details->figure = result_set->getString("figure");
            details->rank = result_set->getInt("rank");
            details->credits = result_set->getInt("credits");
            details->has_logged_in = result_set->getBoolean("has_logged_in");
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);

        std::string error_message = e.what();

        // If MySQL has gone away, we will try again since the database manager would have already reconnected
        if (error_message.find("has gone away") != std::string::npos) {
            return findUserByTicket(player, sso_ticket);
        }
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return details;
}

/*
    Finds session data based on their user id, returns a smart pointer since we still want to use null, but don't need to 
    worry about the lifetime of the object.

    @param user id

    @return SessionData ptr or nullptr (check if this returns nullptr for failure of finding user)
*/
std::shared_ptr<EntityDetails> UserDao::getDetails(int user_id) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    std::shared_ptr<EntityDetails> details = nullptr;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id, username, rank, mission, figure, credits FROM users WHERE id = ? LIMIT 1")); {
            statement->setInt(1, user_id);
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {

            details = std::make_shared<EntityDetails>(nullptr);
            details->id = result_set->getInt("id");
            details->username = result_set->getString("username");
            details->motto = result_set->getString("mission");
            details->figure = result_set->getString("figure");
            details->rank = result_set->getInt("rank");
            details->credits = result_set->getInt("credits");
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return details;
};

/*
    Updates player details

    @param id of the user to update
    @return none
*/

void UserDao::updateUser(int user_id, EntityDetails *details) {

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("UPDATE users SET last_online = ?, has_logged_in = ? WHERE id = ?")); {
            statement->setInt64(1, Icarus::getUnixTimestamp());
            statement->setBoolean(2, details->has_logged_in);
            statement->setInt(3, user_id);

        }

       statement->execute();
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

}