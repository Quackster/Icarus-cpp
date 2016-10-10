#pragma once
#include <map>

class Room; // Defined elsewhere
class RoomUser
{

public:
    RoomUser();
    ~RoomUser();

    Room *getRoom() { return room; }
    void setRoom(Room *room) { this->room = room; }

private:
    int virtual_id;
    int last_chat_id;
    int dance_id;

    int x;
    int y;
    double height;

    int goal_x;
    int goal_y;

    int rotation;
    int headRotation;

    std::map<std::string, std::string> statuses;

    Room *room;

    bool is_walking;
    bool needs_update;
    bool is_loading_room;

public:

};
