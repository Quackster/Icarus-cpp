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

#include "RoomPopulator.h"

class PopularPopulator : public RoomPopulator {

public:
    PopularPopulator() { }
    std::vector<Room*> populate(bool room_limit, Player* player) {

        std::vector<Room*> rooms;

        for (auto kvp : Icarus::getGame()->getRoomManager()->getRooms()) {

            Room *room = kvp.second;

            if (room->getPlayers().size() == 0) {
                continue;
            }

            if (!room->getData()->private_room) {
                continue;
            }

            if (room->getData()->room_state == ROOM_STATE_INVISIBLE) {
                if (!room->hasRights(player)) {
                    continue;
                }
            }

            rooms.push_back(room);
        }

        this->sort(rooms);
        return rooms;
    }
};