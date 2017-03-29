/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "boot/Icarus.h"
#include "communication/incoming/MessageEvent.h"

class PrivateRoomsMessageEvent : public MessageEvent {

public:
    PrivateRoomsMessageEvent() { }

    void handle(Player *player, Request &request) {

        RoomPopulator *populator = Icarus::getGame()->getNavigatorManager()->getPopulator("MyRoomPopulator");
        player->send(SearchResultSetComposer(player, populator));
    }
};