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
    Room();
    ~Room();

    bool hasRights(int user_id, bool owner_check_only = false);

    void serialise(Response &response, bool enter_room);
    void enter(Player* player);
    void leave(Player* player, bool hotel_view, bool dispose = true);
    void dispose(bool force_disposal = false);
    void setRoomData(RoomData *room_data) { this->room_data = room_data; };
    void send(MessageComposer &composer);
    RoomData *getData() { return room_data; }
    std::vector<Player*> getPlayers();
    std::vector<Entity*> *getEntities() { return entities; }
    bool hasEntity(Entity* entity);
    void scheduleRunnable();
    bool isDisposed() { return disposed; }
    //bool isDisposed(bool disposed) { return disposed = disposed; }

private:
    RoomData *room_data;
    RoomRunnable *room_runnable;
    std::vector<Entity*> *entities;
    bool disposed;

    void reset();
};