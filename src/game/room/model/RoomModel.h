/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>
#include <map>

class RoomModel
{

public:
    const static int OPEN = 0;
    const static int CLOSED = 1;

    RoomModel(std::string name, std::string heightmap, int door_x, int door_y, int door_z, int door_rotation);
    ~RoomModel();

    std::string getSquareChar(int x, int y);
    double getSquareHeight(int x, int y);
    const bool isValidSquare(int x, int y);
    std::map<int, std::map<int, int>> &getSquares();

    const int getRandomX();
    const int getRandomY();

    std::string name;
    std::string height_map;
    std::string floor_map;

    int door_x;
    int door_y;
    int door_z;
    int door_rotation;
    int map_size_x;
    int map_size_y;

private:
    std::map<int, std::map<int, std::string>> square_chars;
    std::map<int, std::map<int, int>> squares;
    std::map<int, std::map<int, double>> square_height;
};