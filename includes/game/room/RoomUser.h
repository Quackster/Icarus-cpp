#pragma once
#include <map>

#include "game/pathfinder/Position.h"

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
    int head_rotation;

    std::map<std::string, std::string> statuses;

    Room *room;

    bool is_walking;
    bool needs_update;
    bool is_loading_room;

public:

    void reset();

    bool getLoadingRoom() { return is_loading_room; }
    bool getNeedsUpdate() { return needs_update; }
    bool isWalking() { return is_walking; }
    int getRotation() { return rotation; }
    int getHeadRotation() { return head_rotation; }
    int getGoalX() { return goal_x; }
    int getGoalY() { return goal_y; }
    int getX() { return x; }
    int getY() { return y; }
    std::map<std::string, std::string> &getStatuses() { return statuses;  }
    double getHeight() { return height; }
    int getVirtualId() { return virtual_id; }
    Position getPosition() { return Position(x, y); }
    Position getGoal() { return Position(goal_x, goal_y); }

    void updateStatus(std::string key, std::string value);

    void setLoadingRoom(bool is_loading_room) { this->is_loading_room = is_loading_room; }
    void setNeedsUpdate(bool needs_update) { this->needs_update = needs_update; }
    void setWalking(bool is_walking) { this->is_walking = is_walking; }
    void setRotation(int rotation, bool set_head_rotation = false, bool update = false);
    //void setHeadRotation(int head_rotation) { this->head_rotation = head_rotation; }
    void setGoalX(int goal_x) { this->goal_x = goal_x; }
    void setGoalY(int goal_y) { this->goal_y = goal_y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setHeight(double height) { this->height = height; }
    void setVirtualId(int virtual_id) { this->virtual_id = height; }
};
