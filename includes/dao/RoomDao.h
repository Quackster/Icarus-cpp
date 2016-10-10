#pragma once
#include <vector>
#include <string>

#include "game/room/Room.h"
#include "game/room/RoomManager.h"
#include "game/room/model/RoomModel.h"

#include "mysql_connection.h"
#include "mysql.h"

class RoomDao
{

private:
    RoomDao() { };

public:
    static std::map<std::string, RoomModel*> *getModels();
    static std::vector<int> getPlayerRooms(int user_id);
    static Room* getRoom(int room_id);
    static std::vector<Room*> getRooms(std::vector<int> room_ids);
    static std::vector<int> getRights(int room_id);
};

