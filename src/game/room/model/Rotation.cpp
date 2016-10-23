/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include "stdafx.h"
#include "game/room/model/Rotation.h"

int Rotation::getRotation(int current_x, int current_y, int new_x, int new_y) {

    int rotation = 0;

    if (current_x > new_x && current_y > new_y) {
        rotation = 7;
    }
    else if (current_x < new_x && current_y < new_y) {
        rotation = 3;
    }
    else if (current_x > new_x && current_y < new_y) {
        rotation = 5;
    }
    else if (current_x < new_x && current_y > new_y) {
        rotation = 1;
    }
    else if (current_x > new_x) {
        rotation = 6;
    }
    else if (current_x < new_x) {
        rotation = 2;
    }
    else if (current_y < new_y) {
        rotation = 4;
    }
    else if (current_y > new_y) {
        rotation = 0;
    }

    return rotation;
}