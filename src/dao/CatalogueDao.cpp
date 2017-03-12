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
#include "game/catalogue/CatalogueItem.h"

#include "misc/Utilities.h"

#include <boost/algorithm/string.hpp> 

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
        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT id, parent_id, caption, icon_color, icon_image, min_rank FROM catalog_pages WHERE parent_id = " + std::to_string(id)));

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
std::map<int, CataloguePage*> CatalogueDao::getPages() {

	std::map<int, CataloguePage*> pages;// = new std::vector<NavigatorTab*>();
	std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

	try {

		std::shared_ptr<sql::Connection> sqlConnection = connection->sql_connection;
		std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
		std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT * FROM catalog_pages"));

		while (resultSet->next()) {

			CataloguePage *page = new CataloguePage;
			page->id = resultSet->getInt("id");
			page->caption = resultSet->getString("caption");
			page->type = resultSet->getString("type");
			page->layout = resultSet->getString("page_layout");
			page->minimum_rank = resultSet->getInt("min_rank");

			std::string tmp_images = resultSet->getString("page_images");
			tmp_images = Utilities::removeChar(tmp_images, ']');
			tmp_images = Utilities::removeChar(tmp_images, '[');
			boost::replace_all(tmp_images, "\",\"", "|");

			std::string tmp_texts = resultSet->getString("page_texts");
			tmp_texts = Utilities::removeChar(tmp_texts, ']');
			tmp_texts = Utilities::removeChar(tmp_texts, '[');
			boost::replace_all(tmp_texts, "\",\"", "|");

			if (tmp_images.size() >= 2) {
				tmp_images = tmp_images.substr(1, tmp_images.size() - 2);
			}

			if (tmp_texts.size() >= 2) {

				tmp_texts = tmp_texts.substr(1, tmp_texts.size() - 2);
			}

			for (auto str : Utilities::split(tmp_images, '|')) {
				page->images.push_back(str);
			}

			for (auto str : Utilities::split(tmp_texts, '|')) {

				if (str.back() == '=') {
					str = Utilities::base64_decode(str);
				}

				page->texts.push_back(str);
			}

			pages.insert(std::make_pair(page->id, page));
		}
	}
	catch (sql::SQLException &e) {
		Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
	}

	Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);
	
	return pages;
}

/*
Returns a list of catalogue items inside a vector

@return list of catalogue item
*/
std::vector<CatalogueItem> CatalogueDao::getItems() {

	std::vector<CatalogueItem> items;// = new std::vector<NavigatorTab*>();
	std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

	try {

		std::shared_ptr<sql::Connection> sqlConnection = connection->sql_connection;
		std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
		std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT * FROM catalog_items"));

		while (resultSet->next()) {

			CatalogueItem item;
			item.id = resultSet->getInt("id");
			item.page_id = resultSet->getInt("page_id");
			item.item_id = std::stoi(resultSet->getString("item_ids"));
			item.catalogue_name = resultSet->getString("catalog_name");
			item.cost_credits = resultSet->getInt("cost_credits");
			item.cost_pixels = resultSet->getInt("cost_pixels");
			item.cost_snow = resultSet->getInt("cost_snow");
			item.amount = resultSet->getInt("amount");
			item.vip = resultSet->getInt("vip");
			item.achievement = resultSet->getInt("achievement");
			item.song_id = resultSet->getInt("song_id");
			item.limited_sells = resultSet->getInt("limited_sells");
			item.limited_stack = resultSet->getInt("limited_stack");
			item.achievement = resultSet->getInt("achievement");
			item.offer_active = resultSet->getInt("offer_active") == 1;
			item.extra_data = resultSet->getInt("extradata");
			item.badge_id = resultSet->getString("badge_id");
			item.flat_id = resultSet->getInt("flat_id");
			items.push_back(item);
		}
	}
	catch (sql::SQLException &e) {
		Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
	}

	Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);
	
	return items;
}
