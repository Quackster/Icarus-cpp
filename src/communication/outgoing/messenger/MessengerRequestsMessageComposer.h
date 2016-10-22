/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>

#include "game/player/Player.h"
#include "game/messenger/MessengerUser.h"
#include "communication/outgoing/MessageComposer.h"

class MessengerRequestsMessageComposer : public MessageComposer {

public:
    MessengerRequestsMessageComposer(EntityDetails *details, std::map<int, MessengerUser*> *requests) :
        details(details),
        requests(requests) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->details->getId());
        response.writeInt(this->requests->size());

        for (auto kvp : *requests) {
            response.writeInt(kvp.second->getDetails()->getId());
            response.writeString(kvp.second->getDetails()->getUsername());
            response.writeString(kvp.second->getDetails()->getFigure());
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::MessengerRequestsMessageComposer;
    }

private:
    EntityDetails *details;
    std::map<int, MessengerUser*> *requests;
};