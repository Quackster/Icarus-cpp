#pragma once
#include "stdafx.h"

#include "dao/RoomDao.h"
#include "boot/Icarus.h"
#include "misc/Utilities.h"

/*
    Get list of room ids that the player owns

    @param room id
    @return vector of room ids
*/
std::vector<int> RoomDao::getPlayerRooms(int user_id) {

    std::vector<int> rooms;

    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;
        std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id FROM rooms WHERE owner_id = ? "));
        statement->setInt(1, user_id);

        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

        while (result_set->next()) {
            rooms.push_back(result_set->getInt("id"));
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return rooms;
}

/*
    Get list of room instances by list of room ids

    @param vector room ids
    @return room ptr instances
*/
std::vector<Room*> RoomDao::getRooms(std::vector<int> room_ids) {

    std::vector<Room*> rooms;
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {

        std::shared_ptr<sql::Connection> sql_connection = connection->sqlConnection;

        for (int room_id : room_ids) {

            std::shared_ptr<sql::PreparedStatement> statement = std::shared_ptr<sql::PreparedStatement>(sql_connection->prepareStatement("SELECT id, name, room_type, owner_id, group_id, description, password, users_now, users_max, model, wallpaper, floor, outside, tags, trade_state, state, score, category, allow_pets, allow_pets_eat, allow_walkthrough, hidewall, wall_thickness, floor_thickness, chat_type, chat_balloon, chat_speed, chat_max_distance, chat_flood_protection, who_can_mute, who_can_kick, who_can_ban FROM rooms WHERE id = ? ")); {
                statement->setInt(1, room_id);
            }

            std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery());

            while (result_set->next()) {

                // These pointers get deleted when either
                // 
                // The user leaves the room and they're not the owner, and they're the last one in the room
                // The user disconnects and there's no one else in the room so they get deleted
                //
                // All called from the .dispose function of the Room
                Room *room = new Room();

                room->setRoomData(new RoomData(
                    room_id,
                    result_set->getString("name"),
                    (char)result_set->getInt("room_type"),
                    result_set->getInt("owner_id"),
                    result_set->getInt("group_id"),
                    result_set->getString("description"),
                    result_set->getString("password"),
                    result_set->getInt("users_now"),
                    result_set->getInt("users_max"),
                    result_set->getString("model"),
                    result_set->getString("wallpaper"),
                    result_set->getString("floor"),
                    result_set->getString("outside"),
                    Utilities::split(result_set->getString("tags"), ','),
                    result_set->getInt("trade_state"),
                    result_set->getInt("state"),
                    result_set->getInt("score"),
                    result_set->getInt("category"),
                    result_set->getBoolean("allow_pets"),
                    result_set->getBoolean("allow_pets_eat"),
                    result_set->getBoolean("allow_walkthrough"),
                    result_set->getBoolean("hidewall"),
                    result_set->getInt("wall_thickness"),
                    result_set->getInt("floor_thickness"),
                    result_set->getInt("chat_type"),
                    result_set->getInt("chat_balloon"),
                    result_set->getInt("chat_speed"),
                    result_set->getInt("chat_max_distance"),
                    result_set->getInt("chat_flood_protection"),
                    result_set->getInt("who_can_mute"),
                    result_set->getInt("who_can_kick"),
                    result_set->getInt("who_can_ban")
                 ));

                rooms.push_back(room);
            }
        }

    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return rooms;
}


