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
#include "ItemDao.h"

std::map<int, ItemDefinition*> ItemDao::getItemDefinitions() {

	std::map<int, ItemDefinition*> furnitures;
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sql_connection->createStatement());
        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery("SELECT * FROM furniture"));

		while (result_set->next()) {
			
			ItemDefinition *furni = new ItemDefinition();
			furni->id = result_set->getInt("id");
			furni->public_name = result_set->getString("public_name");
			furni->item_name = result_set->getString("item_name");
			furni->width = result_set->getInt("width");
			furni->length = result_set->getInt("length");

			std::string::size_type sz;
			furni->stack_height = std::stod(result_set->getString("stack_height"), &sz);

			furni->type = result_set->getString("type");

			furni->can_stack = result_set->getInt("can_stack") == 1;
			/**/furni->can_sit = result_set->getInt("can_sit") == 1;
			furni->sprite_id = result_set->getInt("sprite_id");

			furni->is_walkable = result_set->getInt("is_walkable") == 1;
			furni->allow_gift = result_set->getInt("allow_gift") == 1;
			furni->allow_trade = result_set->getInt("allow_trade") == 1;
			furni->allow_inventory_stack = result_set->getInt("allow_inventory_stack") == 1;
			furni->allow_marketplace_sell = result_set->getInt("allow_marketplace_sell") == 1;
			furni->allow_recycle = result_set->getInt("allow_recycle") == 1;
			furni->interaction_type = result_set->getString("interaction_type");
			furni->vending_id = std::stoi(result_set->getString("vending_ids"));
		    furni->effect_id = result_set->getInt("effectid");
			//furni->height_adjustible = resultSet->getInt("height_adjustible");
			furni->flat_id = result_set->getInt("flat_id");
			furni->song_id = result_set->getInt("song_id");
			furni->requires_rights = result_set->getInt("requires_rights") == 1;
			furni->is_arrow = result_set->getInt("is_arrow");
			furnitures.insert(std::make_pair(furni->id, furni));

		}
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return furnitures;
}
