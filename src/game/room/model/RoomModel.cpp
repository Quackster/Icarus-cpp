#include "stdafx.h"

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <sstream>

#include "misc/Utilities.h"
#include "game/room/model/RoomModel.h"

/*
    Constructor for RoomModel
*/
RoomModel::RoomModel(std::string name, std::string height_map, int door_x, int door_y, int door_z, int door_rotation)
    : name(name), height_map(height_map), door_x(door_x), door_y(door_y), door_z(door_z), door_rotation(door_rotation) {

    std::vector<std::string> temporary = Utilities::split(this->height_map, (char)13);

    this->map_size_x = temporary[0].length();
    this->map_size_y = temporary.size();


    for (int y = 0; y < map_size_y; y++) {

        if (y > 0) {
            temporary[y] = temporary[y].substr(1); 
        }

        for (int x = 0; x < map_size_x; x++) {

            std::string square = temporary[y];
            square = square.substr(x).substr(0, 1);

            boost::algorithm::trim(square);
            boost::algorithm::to_lower(square);

            if (Utilities::isNumber(square)) {
                this->square_height[x][y] = stoi(square);
                this->squares[x][y] = 0;
            }
            else if (square == "x") {
                this->squares[x][y] = 1;
            }
            
            this->square_char[x][y] = square;
        }
    }

    std::stringstream ss;

    for (int y = 0; y < map_size_y; y++) {
        for (int x = 0; x < map_size_x; x++) {

            if (x == this->door_x && y == this->door_y) {
                ss << this->door_z;
            }
            else {
                ss << this->square_char[x][y];
            }
        }
        
        ss << (char)13;
    }
    
    
    this->floor_map = ss.str();
}

/*
    Deconstructor for RoomModel
*/
RoomModel::~RoomModel() {

}