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

#include "boot/Icarus.h"
#include "dao/NavigatorDao.h"

#include "DisposablePopulator.h"
#include "RoomPopulator.h"
#include "FriendsPopulator.h"

class FriendsPopulator : public RoomPopulator, public DisposablePopulator {

public:
    FriendsPopulator() { }

    std::vector<Room*> populate(bool room_limit, Player* player) {

        std::vector<Room*> rooms = NavigatorDao::getPreviewRooms(NAVIGATOR_FRIENDS_ROOMS, player->getDetails()->id);
        return rooms;
    }

    /*
        Since this class only uses temporary pointers, we dispose them when they're no longer needed.
        The system fundementally uses pointers for rooms - so this is required in order to stop memory leaks.

        @param room list
        @return none
    */
    void dispose(std::vector<Room*> rooms) {
        for (Room *room : rooms) {
            delete room;
        }
    }
};