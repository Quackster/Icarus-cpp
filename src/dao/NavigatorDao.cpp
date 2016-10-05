#pragma once
#include "stdafx.h"

#include "dao/NavigatorDao.h"
#include "boot/Icarus.h"

/*
    Finds tabs by child id, if id is -1 it will return parent tabs

    @param child id
    @return list of tabs
*/
vector<NavigatorTab*> *NavigatorDao::getTabsByChildId(int child_id) {

    vector<NavigatorTab*> *tabs = new vector<NavigatorTab*>();
    
    shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        shared_ptr<sql::Statement> statement = shared_ptr<sql::Statement>(sql_connection->createStatement());
        shared_ptr<sql::ResultSet> result_set = shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, child_id, tab_name, title, button_type, closed, thumbnail, room_populator FROM navigator_tabs WHERE child_id = " + std::to_string(child_id)));

        while (result_set->next()) {

            NavigatorTab *tab = new NavigatorTab(
                result_set->getInt("id"),
                result_set->getInt("child_id"),
                result_set->getString("tab_name"),
                result_set->getString("title"),
                (char)result_set->getInt("button_type"),
                result_set->getBoolean("closed"),
                result_set->getBoolean("thumbnail")
            );

            tabs->push_back(tab);
            
            // Also add child tabs
            auto child_tabs = shared_ptr<vector<NavigatorTab*>>(getTabsByChildId(tab->getId()));
            tabs->insert(tabs->end(), child_tabs->begin(), child_tabs->end());
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
vector<NavigatorCategory*> *NavigatorDao::getCategories() {

    vector<NavigatorCategory*> *categories = new vector<NavigatorCategory*>();

    shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        shared_ptr<sql::Statement> statement = shared_ptr<sql::Statement>(sql_connection->createStatement());
        shared_ptr<sql::ResultSet> result_set = shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, title, min_rank FROM navigator_categories"));

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
