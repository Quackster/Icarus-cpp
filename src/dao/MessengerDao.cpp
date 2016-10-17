/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "dao/MessengerDao.h"
#include "boot/Icarus.h"

std::map<int, MessengerUser*> *MessengerDao::getFriends(int user_id) {

    std::map<int, MessengerUser*> *friends = new std::map<int, MessengerUser*>();

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        std::shared_ptr<sql::Connection> sqlConnection = connection->sqlConnection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT * FROM messenger_friendships WHERE (sender = " + std::to_string(user_id) + ") OR (receiver = " + std::to_string(user_id) + ")"));

        while (resultSet->next()) {

            MessengerUser *friend_;

            if (resultSet->getInt("sender") != user_id) {
                friend_ = new MessengerUser(resultSet->getInt("sender"));
            }
            else {
                friend_ = new MessengerUser(resultSet->getInt("receiver"));
            }

            friends->insert(std::make_pair(friend_->getDetails()->getId(), friend_));
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return friends;
}

std::map<int, MessengerUser*> *MessengerDao::getRequests(int user_id) {

    std::map<int, MessengerUser*> *friends = new std::map<int, MessengerUser*>();

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        std::shared_ptr<sql::Connection> sqlConnection = connection->sqlConnection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT * FROM messenger_requests WHERE to_id = " + std::to_string(user_id)));

        while (resultSet->next()) {

            MessengerUser *friend_ = new MessengerUser(resultSet->getInt("from_id"));
            friends->insert(std::make_pair(friend_->getDetails()->getId(), friend_));
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return friends;

}

std::vector<int> MessengerDao::search(std::string query) {

    std::vector<int> results;

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id FROM users WHERE username LIKE ? LIMIT 30")); {
            statement->setString(1, "%" + query + "%");
        }

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {
            results.push_back(result_set->getInt("id"));
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return results;
}

bool MessengerDao::newRequest(int fromId, int toId) {

    return true;
}

bool MessengerDao::removeRequest(int fromId, int toId) {

    return true;
}

bool MessengerDao::newFriend(int sender, int receiver) {

    return true;
}