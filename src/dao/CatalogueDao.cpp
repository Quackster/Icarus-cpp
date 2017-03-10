/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "boot/Icarus.h"

#include "mysql_connection.h"
#include "mysql.h"

#include "dao/CatalogueDao.h"

#include "game/catalogue/CatalogueTab.h"
#include "game/catalogue/CataloguePage.h"

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

/*
	Returns a list of catalogue page instances inside a vector
	@return list of catalogue pages
*/
std::map<int, CataloguePage> CatalogueDao::getPages() {

	std::map<int, CataloguePage> pages;// = new std::vector<NavigatorTab*>();
	std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

	try {

		std::shared_ptr<sql::Connection> sqlConnection = connection->sql_connection;
		std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
		std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT * FROM catalogue_pages"));

		while (resultSet->next()) {

			CataloguePage page;
			/*tab.id = resultSet->getInt("id");
			tab.parent_id = resultSet->getInt("parent_id");
			tab.caption = resultSet->getString("caption");
			tab.icon_colour = resultSet->getInt("icon_color");
			tab.icon_image = resultSet->getInt("icon_image");
			tab.min_rank = resultSet->getInt("min_rank");
			tabs.push_back(tab);*/

			page.id = resultSet->getInt("id");
			page.layout = resultSet->getString("page_layout");
			page.headline = resultSet->getString("page_headline");
			page.teaser = resultSet->getString("page_teaser");
			page.special = resultSet->getString("page_special");
			page.text1 = resultSet->getString("page_text1");
			page.text2 = resultSet->getString("page_text2");
			page.text_details = resultSet->getString("page_text_details");
			page.text_teaser = resultSet->getString("page_text_teaser");
			pages.insert(std::make_pair(page.id, page));
		}
	}
	catch (sql::SQLException &e) {
		Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
	}

	Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

	return pages;
}
