/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <map>

#include "game/pathfinder/Position.h"

class ItemDefinition;
class Response;
class Item
{
public:
    Item(int id, int user_id, int owner_id, int item_id, int room_id, std::string x, std::string y, double z, int rotation, std::string extra_data);
    ~Item();
    
    std::string getWallPosition();
    void parseWallPosition(std::string position);

    void updateEntities();
    bool hasEntityCollision(int x, int y);
    void save();
    void remove();

    bool isWallItem();
    bool isFloorItem();

    std::map<int, Position> getAffectedTiles();
    void serialise(Response &response);

    ItemDefinition *getDefinition() { return this->item_definition; }

    int id = -1;
    int user_id = -1;
    int owner_id = -1;
    std::string owner_name = "";
    int item_id = -1;
    int room_id = -1;
    int x = -1;
    int y = -1;
    double z = 0;
    int rotation = 0;
    std::string extra_data = "";

    char side;
    int width_x;
    int width_y;
    int length_x;
    int length_y;

private:
    ItemDefinition *item_definition = nullptr;
};

