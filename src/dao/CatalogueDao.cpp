/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "dao/CatalogueDao.h"

#include "boot/Icarus.h"

#include "game/catalogue/CatalogueTab.h"

/*
    Finds tabs by child id, if id is -1 it will return parent tabs

    @param child id
    @return list of tabs
*/
std::vector<CatalogueTab> CatalogueDao::getTabs(int id) {

    std::vector<CatalogueTab> tabs;// = new std::vector<NavigatorTab*>();
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sqlConnection = connection->sql_connection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, parent_id, caption, icon_color, icon_image, min_rank FROM catalogue_pages WHERE parent_id = " + std::to_string(id)));

		while (resultSet->next()) {

			CatalogueTab tab;
			tab.id = resultSet->getInt("id");
			tab.parent_id = resultSet->getInt("parent_id");
			tab.caption = resultSet->getString("caption");
			tab.icon_colour = resultSet->getInt("icon_color");
			tab.icon_image = resultSet->getInt("icon_image");
			tab.min_rank = resultSet->getInt("min_rank");
			tabs.push_back(tab);
		}
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return tabs;
}
