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

    std::string getSquareChar(int x, int y) const { return this->square_char[x * map_size_y + y]; }
    double getSquareHeight(int x, int y) const { return this->square_height[x * map_size_y + y]; }
    const bool isValidSquare(int x, int y) const { return squares[x * map_size_y + y] == 0; }
    
    int *getSquares() { return squares; }

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
    std::string *square_char;// [MAX_SIZE_X][MAX_SIZE_Y];
    int *squares;
    double *square_height;
};