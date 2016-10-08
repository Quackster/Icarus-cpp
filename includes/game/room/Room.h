#pragma once
#include "game/room/RoomData.h"
class Room
{
public:
    Room();
    ~Room();

    void dispose(bool force_disposal = false);

    void setRoomData(RoomData *room_data) { this->room_data = room_data; };
    RoomData *getData() { return room_data; }

private:
    RoomData *room_data;
};

