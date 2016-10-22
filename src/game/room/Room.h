/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <map>
#include <vector>

#include "communication/streams/Response.h"
#include "game/entities/Entity.h"
#include "game/player/Player.h"
#include "game/room/RoomData.h"
#include "game/room/tasks/RoomRunnable.h"

class Room
{
public:
    Room(int room_id);
    ~Room();

    bool hasRights(const int user_id, const bool owner_check_only = false);
    void serialise(Response &response, const bool enter_room = false);
    void enter(Player *player);
    void leave(Player *player, const bool hotel_view, const bool dispose = true);
    void dispose(const bool force_disposal = false);
    void setRoomData(RoomData *room_data) { this->room_data = room_data; };
    void send(const MessageComposer &composer);
    void scheduleRunnable();


    ////
    //  Getters and setters
    ////
    int getId() { return this->room_data->getId(); }
  
    RoomData *getData() { return room_data; }
    RoomModel *getModel() { return this->room_data->getModel(); }
    const std::vector<Player*> getPlayers();
    
    std::map<int, Entity*> *getEntities() { return entities; }
    std::shared_ptr<RoomRunnable> getRunnable() { return this->runnable; }
    void setRunnable(std::shared_ptr<RoomRunnable> runnable) { this->runnable = runnable; }

    bool hasEntity(Entity *entity);
    bool isDisposed() { return disposed; }

private:

    int room_id;

    RoomData *room_data;
    std::shared_ptr<RoomRunnable> runnable;
    std::map<int, Entity*> *entities;

    bool disposed;
    void reset();
};