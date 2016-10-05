#pragma once
#include "stdafx.h"

#include "dao/NavigatorDao.h"
#include "boot/Icarus.h"

/*
    Finds tabs by child id, if id is -1 it will return parent tabs

    @param child id
    @return list of tabs
*/
vector<NavigatorTab> *NavigatorDao::findTabsByChildId(int child_id) {

    vector<NavigatorTab> *tabs = new vector<NavigatorTab>();
    
    shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();
    bool has_user = false;

    try {

        shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        shared_ptr<sql::PreparedStatement> statement = shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id, child_id, tab_name, title, button_type, closed, thumbnail, room_populator FROM navigator_tabs WHERE child_id = " + child_id));
        shared_ptr<sql::ResultSet> result_set = shared_ptr<sql::ResultSet>(statement->executeQuery());

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
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return tabs;
}
