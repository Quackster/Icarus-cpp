#pragma once
#include <string>

class RoomModel
{

public:
     const static int OPEN = 0;
     const static int CLOSED = 1;

     RoomModel(std::string name, std::string heightmap, int door_x, int door_y, int door_z, int door_rotation);

     std::string &getName() { return name; }
     std::string &getHeightMap() { return height_map; }
     std::string &getFloorMap() { return floor_map; }
     std::string **getSquareChar() { return square_char; }
     int **getSquareHeight() { return square_height; }
     int **getSquares() { return squares; }
     int getMapSizeX() { return this->map_size_x; }
     int getMapSizeY() { return this->map_size_y; }

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
    std::string **square_char;// [MAX_SIZE_X][MAX_SIZE_Y];

    int door_x;
    int door_y;
    int door_z;
    int door_rotation;
    int map_size_x;
    int map_size_y;

    int **squares;
    int **square_height;
};