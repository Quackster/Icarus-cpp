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
     int* getSquares() { return squares; }

     int getMapSizeX() { return this->map_size_x; }
     int getMapSizeY() { return this->map_size_y; }

     int getDoorX() { return this->door_x; }
     int getDoorY() { return this->door_y; }
     int getDoorZ() { return this->door_z; }
     int getDoorRotation() { return this->door_rotation; }

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