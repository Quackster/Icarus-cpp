/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

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

    bool hasRights(int user_id, bool owner_check_only = false);

    void serialise(Response &response);
    void enter(Player* player);
    void leave(Player* player, bool hotel_view, bool dispose = true);
    void dispose(bool force_disposal = false);
    void setRoomData(RoomData *room_data) { this->room_data = room_data; };
    void send(const MessageComposer &composer);
    int getId() { return this->room_data->getId(); }
    RoomData *getData() { return room_data; }
    RoomModel *getModel() { return this->room_data->getModel(); }
    std::vector<Player*> getPlayers();
    std::vector<Entity*> *getEntities() { return entities; }

    bool hasEntity(Entity* entity);
    void scheduleRunnable();
    bool isDisposed() { return disposed; }
    std::shared_ptr<RoomRunnable> getRunnable() { return this->runnable; }
    void setRunnable(std::shared_ptr<RoomRunnable> runnable) { this->runnable = runnable; }
    //bool isDisposed(bool disposed) { return disposed = disposed; }

private:

    int room_id;

    RoomData *room_data;
    std::shared_ptr<RoomRunnable> runnable;
    std::vector<Entity*> *entities;

    bool disposed;
    void reset();
};