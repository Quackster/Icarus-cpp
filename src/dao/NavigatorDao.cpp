/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "dao/NavigatorDao.h"
#include "boot/Icarus.h"

int NavigatorDao::createRoom(std::string room_name, std::string description, std::string room_model, int owner_id, int category, int max_users, int trade_settings) {

    int room_id = -1;

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        // Insert room data
        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("INSERT INTO rooms (name, description, owner_id, model, category, users_max, trade_state) VALUES (?, ?, ?, ?, ?, ?, ?);")); {
            statement->setString(1, room_name);
            statement->setString(2, description);
            statement->setInt(3, owner_id);
            statement->setString(4, room_model);
            statement->setInt(5, category);
            statement->setInt(6, max_users);
            statement->setInt(7, trade_settings);
            statement->executeUpdate();
        }

        // Last inserted id
        std::shared_ptr<sql::Statement> stmnt = std::shared_ptr<sql::Statement>(sql_connection->createStatement()); {
            auto result_set = stmnt->executeQuery("SELECT LAST_INSERT_ID() as id;");
            result_set->next();
            room_id = result_set->getInt("id");
        }
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return room_id;
}

/*
    Finds tabs by child id, if id is -1 it will return parent tabs

    @param child id
    @return list of tabs
*/
std::vector<NavigatorTab*> NavigatorDao::getTabsByChildId(int child_id) {

    std::vector<NavigatorTab*> tabs;// = new std::vector<NavigatorTab*>();
    
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sql_connection->createStatement());
        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, child_id, tab_name, title, button_type, closed, thumbnail, room_populator FROM navigator_tabs WHERE child_id = " + std::to_string(child_id)));

        while (result_set->next()) {

            NavigatorTab *tab = new NavigatorTab(
                result_set->getInt("id"),
                result_set->getInt("child_id"),
                result_set->getString("tab_name"),
                result_set->getString("title"),
                (char)result_set->getInt("button_type"),
                result_set->getBoolean("closed"),
                result_set->getBoolean("thumbnail"),
                result_set->getString("room_populator")

            );

            tabs.push_back(tab);
            
            // Also add child tabs
            auto childTabs = std::vector<NavigatorTab*>(getTabsByChildId(tab->getId()));
            tabs.insert(tabs.end(), childTabs.begin(), childTabs.end());
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return tabs;
}

/*
    Get all categories

    @return vector ptr categories
*/
std::vector<NavigatorCategory*> NavigatorDao::getCategories() {

    std::vector<NavigatorCategory*> categories;// = new std::vector<NavigatorCategory*>();
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sql_connection->createStatement());
        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, title, min_rank FROM navigator_categories"));

        while (result_set->next()) {

            NavigatorCategory *category = new NavigatorCategory();
            category->id = result_set->getInt("id");
            category->name = result_set->getString("title");
            category->minimum_rank = result_set->getInt("min_rank");

            categories.push_back(category);
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return categories;
}
