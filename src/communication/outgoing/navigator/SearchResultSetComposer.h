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

#include "game/navigator/populators/DisposablePopulator.h"

#include "game/player/Player.h"
#include "game/navigator/NavigatorTab.h"
#include "communication/outgoing/MessageComposer.h"

class SearchResultSetComposer : public MessageComposer {

public:
    SearchResultSetComposer(Player *player, RoomPopulator *populator) :
        player(player),
        populator(populator) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(0);
        response.writeInt(5);
        response.writeString("");

        if (populator == nullptr) {
            response.writeInt(0);
        } 
        else {
            std::vector<Room*> rooms = populator->populate(false, player);

            response.writeInt(rooms.size());

            for (Room *room : rooms) {
                room->serialise(response);
            }

            DisposablePopulator *disposable = dynamic_cast<DisposablePopulator*>(populator);

            if (disposable) {
                disposable->dispose(rooms);
            }

        } 
        return response;
    }

    const int getHeader() const {
        return Outgoing::SearchResultSetComposer;
    }

private:
    Player *player;
    RoomPopulator *populator;
};