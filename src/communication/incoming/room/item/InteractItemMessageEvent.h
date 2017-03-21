/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/item/Item.h"
#include "game/room/Room.h"

#include "game/item/interactor/BaseInteractor.h"

#include "communication/incoming/MessageEvent.h"

class InteractItemMessageEvent : public MessageEvent {

public:
    InteractItemMessageEvent() { }

    void handle(Player *player, Request &request) {
    
    
        if (!player->getRoomUser()->in_room) {
            return;
        }

        Room *room = player->getRoomUser()->getRoom();

        if (!room->hasRights(player)) {
            return;
        }

        int item_id = request.readInt();

        Item *item = room->getItem(item_id);

        if (item == nullptr) {
            return;
        }

        BaseInteractor *interactor = item->getInteractor();
        
        if (interactor != nullptr) {
            interactor->onInteract(room, item);
        }
    }
};