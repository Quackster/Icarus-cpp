/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "mysql_connection.h"
#include "mysql.h"

#include "boot/Icarus.h"
#include "FurnitureDao.h"

std::map<int, Furniture> FurnitureDao::getFurniture() {

	std::map<int, Furniture> furnitures;
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sqlConnection = connection->sql_connection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sqlConnection->createStatement());
        std::shared_ptr<sql::ResultSet> resultSet = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT * FROM furniture"));

		while (resultSet->next()) {
			
			Furniture furni;
			furni.id = resultSet->getInt("id");
			furni.public_name = resultSet->getString("public_name");
			furni.item_name = resultSet->getString("item_name");
			furni.width = resultSet->getInt("width");
			furni.length = resultSet->getInt("length");

			std::string::size_type sz;
			furni.stack_height = std::stod(resultSet->getString("stack_height"), &sz);

			furni.can_stack = resultSet->getInt("can_stack") == 1;
			/**/furni.can_sit = resultSet->getInt("can_sit") == 1;
			furni.sprite_id = resultSet->getInt("sprite_id");
			furni.is_walkable = resultSet->getInt("is_walkable") == 1;
			furni.allow_gift = resultSet->getInt("allow_gift") == 1;
			furni.allow_trade = resultSet->getInt("allow_trade") == 1;
			furni.allow_inventory_stack = resultSet->getInt("allow_inventory_stack") == 1;
			furni.allow_marketplace_sell = resultSet->getInt("allow_marketplace_sell") == 1;
			furni.allow_recycle = resultSet->getInt("allow_recycle") == 1;
			furni.interaction_type = resultSet->getString("interaction_type");
			furni.vending_id = std::stoi(resultSet->getString("vending_ids"));
		    furni.effect_id = resultSet->getInt("effectid");
			//furni.height_adjustible = resultSet->getInt("height_adjustible");
			furni.flat_id = resultSet->getInt("flat_id");
			furni.song_id = resultSet->getInt("song_id");
			furni.requires_rights = resultSet->getInt("requires_rights") == 1;
			furni.is_arrow = resultSet->getInt("is_arrow");
			furnitures.insert(std::make_pair(furni.id, furni));

		}
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return furnitures;
}
