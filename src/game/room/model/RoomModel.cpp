#include "stdafx.h"

#include "game/room/model/RoomModel.h"

/*
    Constructor for RoomModel
*/
RoomModel::RoomModel(std::string name, std::string height_map, int door_x, int door_y, int door_z, int door_rotation)
    : name(name), height_map(height_map), door_x(door_x), door_y(door_y), door_z(door_z), door_rotation(door_rotation) { }

/*
    Deconstructor for RoomModel
*/
RoomModel::~RoomModel() {


}