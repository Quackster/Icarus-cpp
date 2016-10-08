#pragma once
#include <vector>
#include <string>

#include "game/room/Room.h"
#include "game/room/RoomManager.h"

#include "mysql_connection.h"
#include "mysql.h"

class RoomDao
{

private:
    RoomDao() { };

public:
    static std::vector<int> RoomDao::getPlayerRooms(int user_id);
    static std::vector<Room*> getRooms(std::vector<int> room_ids);

};

