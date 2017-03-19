/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/catalogue/CatalogueItem.h"
#include "communication/outgoing/MessageComposer.h"

class PurchaseNotificationMessageComposer : public MessageComposer {

public:
    PurchaseNotificationMessageComposer(CatalogueItem *item, int amount) :
        item(item),
        amount(amount) { }

    const Response compose() const {
        Response response = this->createResponse();
        item->serialise(response);
        return response;
    }

    const int getHeader() const {
        return Outgoing::PurchaseNotificationMessageComposer;
    }

private:
    CatalogueItem *item;
    int amount;
};