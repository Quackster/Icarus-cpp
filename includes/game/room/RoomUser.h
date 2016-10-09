#pragma once
#include <map>

class RoomUser
{

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


    bool is_walking;
    bool needs_wpdate;

public:

};
