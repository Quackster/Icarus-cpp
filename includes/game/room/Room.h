#pragma once

#include <vector>

#include "communication/streams/Response.h"
#include "game/entities/Entity.h"
#include "game/room/RoomData.h"

class Room
{
public:
    Room();
    ~Room();

    void serialise(Response &response, bool enter_room);
    void dispose(bool force_disposal = false);

    void setRoomData(RoomData *room_data) { this->room_data = room_data; };
    
    RoomData *getData() { return room_data; }
    std::vector<Entity*> *getEntities() { return entities; }

private:
    RoomData *room_data;
    std::vector<Entity*> *entities;
};