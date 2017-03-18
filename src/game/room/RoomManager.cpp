/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "dao/RoomDao.h"

#include "misc/RoomNewbie.h"
#include "game/item/definitions/ItemDefinition.h"

/*
    Constructor for room manager
*/
RoomManager::RoomManager() :
    rooms(std::map<int, Room*>()), 
    public_rooms(std::vector<Room*>()),
    models(RoomDao::getModels()),
	rooms_newbie(RoomDao::getNewbieRoomSelection()) {}

/*
    Loads new player rooms if they're not already added to memory

    @param user id
    @return none
*/
void RoomManager::createPlayerRooms(int user_id) {

    std::vector<int> room_ids = RoomDao::getPlayerRooms(user_id);
    std::vector<int> load_rooms;

    // Do checks to make sure we only load rooms that haven't been loaded
    for (int room_id : room_ids) {
        if (!this->hasRoom(room_id)) {
            load_rooms.push_back(room_id);
        }
    }

    std::vector<Room*> rooms = RoomDao::getRooms(load_rooms);

    for (Room *room : rooms) {
        this->addRoom(room);
    }
}

/*
    Get player rooms by user id
    
    @param user id
    @return vector room ptrs
*/
std::vector<Room*> RoomManager::getPlayerRooms(int user_id) {

    std::vector<Room*> rooms;

    for (auto kvp : this->rooms) {

        Room* room = kvp.second;

        if (room->getData()->owner_id == user_id) {
            rooms.push_back(room);
        }
    }

    return rooms;
}

/*
    Returns model ptr by string

    @param model id
    @return model ptr
*/
RoomModel *RoomManager::getModel(std::string model_id) {

    if (this->models.count(model_id)) {
        return this->models.find(model_id)->second;
    }

    return nullptr;
}

/*
    Returns boolean value true / false if room id exists

    @param room id
    @return if room id is in map or not
*/
bool RoomManager::hasRoom(int room_id) {
    return this->rooms.count(room_id) == 1 ? true : false;
}

/*
    Gets single room by room id

    @param room id
    @return Room ptr
*/
Room *RoomManager::getRoom(int room_id) {

	if (!this->hasRoom(room_id)) {
		this->addRoom(RoomDao::getRoom(room_id));
	}

    if (this->hasRoom(room_id)) {
        return this->rooms.find(room_id)->second;
	}

    return nullptr;
}

/*
    Adds room to map, will not add if room id is already existing

    @param room ptr instance
    @return none
*/
void RoomManager::addRoom(Room *room) {

    if (!this->hasRoom(room->id)) {
        this->rooms.insert(std::make_pair(room->id, room));
    }
}

/*
    Totally deletes from within room manager

    @param room_id
    @return none
*/
void RoomManager::deleteRoom(int room_id) {

    if (this->hasRoom(room_id)) {

        Room *room = this->getRoom(room_id);
        this->rooms.erase(room_id);
        delete room;
    }
}

/*
    Deconstructor for Room Manager
*/
RoomManager::~RoomManager() {

    for (auto room_entry : this->rooms) delete room_entry.second;
    for (auto model_entry : this->models) delete model_entry.second;

    /*delete this->rooms;
    delete this->public_rooms;
    delete this->models;*/
}
