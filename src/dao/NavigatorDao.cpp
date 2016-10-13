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

/*
    Finds tabs by child id, if id is -1 it will return parent tabs

    @param child id
    @return list of tabs
*/
std::vector<NavigatorTab*> *NavigatorDao::getTabsByChildId(int child_id) {

    std::vector<NavigatorTab*> *tabs = new std::vector<NavigatorTab*>();
    
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        std::shared_ptr<sql::Connection> sqlConnection = connection->sqlConnection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, child_id, tab_name, title, button_type, closed, thumbnail, room_populator FROM navigator_tabs WHERE child_id = " + std::to_string(child_id)));

        while (resultSet->next()) {

            NavigatorTab *tab = new NavigatorTab(
                resultSet->getInt("id"),
                resultSet->getInt("child_id"),
                resultSet->getString("tab_name"),
                resultSet->getString("title"),
                (char)resultSet->getInt("button_type"),
                resultSet->getBoolean("closed"),
                resultSet->getBoolean("thumbnail"),
                resultSet->getString("room_populator")

            );

            tabs->push_back(tab);
            
            // Also add child tabs
            auto childTabs = std::shared_ptr<std::vector<NavigatorTab*>>(getTabsByChildId(tab->getId()));
            tabs->insert(tabs->end(), childTabs->begin(), childTabs->end());
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
std::vector<NavigatorCategory*> *NavigatorDao::getCategories() {

    std::vector<NavigatorCategory*> *categories = new std::vector<NavigatorCategory*>();
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sql_connection->createStatement());
        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, title, min_rank FROM navigator_categories"));

        while (result_set->next()) {

            NavigatorCategory *category = new NavigatorCategory(
                result_set->getInt("id"),
                result_set->getString("title"),
                result_set->getInt("min_rank")
            );

            categories->push_back(category);
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return categories;
}
