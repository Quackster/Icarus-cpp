/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "communication/outgoing/MessageComposer.h"
#include "game/item/Item.h"

class WallItemsMessageComposer : public MessageComposer {

public:
    WallItemsMessageComposer(std::vector<Item*> items) :
        items(items) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->items.size());

        for (Item *item : this->items) {
            response.writeInt(item->user_id);
            response.writeString(item->owner_name);
        }

        response.writeInt(this->items.size());

        for (Item *item : this->items) {
            item->serialise(response);
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::WallItemsMessageComposer;
    }

private:
    std::vector<Item*> items;
};