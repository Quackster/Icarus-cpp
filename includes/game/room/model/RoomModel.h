#pragma once
#include <string>

class RoomModel
{

public:
     const static int OPEN = 0;
     const static int CLOSED = 1;

     RoomModel(std::string name, std::string heightmap, int door_x, int door_y, int door_z, int door_rotation);
     ~RoomModel();

private:
    std::string name;
    std::string height_map;
    std::string floor_map;
    std::string square_char[300][300];

    int door_x;
    int door_y;
    int door_z;
    int door_rotation;
    int map_size_x;
    int map_size_y;

    int squares[300][300];
    int square_height[300][300];
};