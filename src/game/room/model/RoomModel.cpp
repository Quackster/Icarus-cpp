#include "stdafx.h"

#include <boost/algorithm/string.hpp>

#include <iostream>

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

    this->squares = new int*[this->map_size_x];
    this->square_char = new std::string*[this->map_size_x];
    this->square_height = new int*[this->map_size_x];

    //std::cout << "(" << this->map_size_x << ", " << this->map_size_y << ") " << std::endl;

    for (int y = 0; y < map_size_y; y++) {

        if (y > 0) {
            temporary[y] = temporary[y].substr(1); 
            //std::cout << temporary[y] << std::endl;
        }

        for (int x = 0; x < map_size_x; x++) {

            this->squares[x] = new int[this->map_size_y];
            this->square_height[x] = new int[this->map_size_y];
            this->square_char[x] = new std::string[this->map_size_y];

            std::string square = temporary[y] + "";
            square = square.substr(x).substr(0, 1);

            boost::algorithm::trim(square);
            boost::algorithm::to_lower(square);
            

            if (square == "x") {
                squares[x][y] = CLOSED;

            }
            else if (Utilities::isNumber(square)) {

                squares[x][y] = OPEN;
                square_height[x][y] = atof(square.c_str());
            }


            if (this->door_x == x && this->door_y == y) {
                squares[x][y] = OPEN;

                std::string str_door_z = this->door_z + "";

                square_height[x][y] = atof(str_door_z.c_str());
            }

            square_char[x][y] = "" + square;

        }
    }

    std::string builder;

    for (int i = 0; i < this->map_size_y; i++) {
        for (int j = 0; j < this->map_size_x; j++) {

            try {

                if (j == this->door_x && i == this->door_y) {
                    builder = builder + ("" + this->door_z);
                }
                else {
                    builder = builder + ("" + this->square_char[j][i]);
                }
            }
            catch (std::exception &e) {
                builder = builder + "0";
            }
        }
        builder = builder + (char)13;
    }

    this->floor_map = builder;
}

/*
    Deconstructor for RoomModel
*/
RoomModel::~RoomModel() {

    delete this->squares;
    delete this->square_char;
    delete this->square_height;
}