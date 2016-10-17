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

    std::string getName() { return name; }
    std::string getHeightMap() { return height_map; }
    std::string getFloorMap() { return floor_map; }

    std::string *getSquareChar() { return square_char; }
    
    double *getSquareHeight() { return square_height; }
    int *getSquares() { return squares; }
    const bool isValidSquare(int x, int y) const { return squares[x * map_size_y + y] == 0; }

    const int &getMapSizeX() const { return this->map_size_x; }
    const int &getMapSizeY() const { return this->map_size_y; }
    const int &getDoorX() const { return this->door_x; }
    const int &getDoorY() const { return this->door_y; }
    const int &getDoorZ() const { return this->door_z; }
    const int &getDoorRotation() const { return this->door_rotation; }

    ~RoomModel();

private:

    enum
    {
        MAX_SIZE_X = 50,
        MAX_SIZE_Y = 50,
    };

    std::string name;
    std::string height_map;
    std::string floor_map;

    int door_x;
    int door_y;
    int door_z;
    int door_rotation;
    int map_size_x;
    int map_size_y;

    std::string *square_char;// [MAX_SIZE_X][MAX_SIZE_Y];
    int *squares;
    double *square_height;
};