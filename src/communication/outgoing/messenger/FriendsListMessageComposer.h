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
#include <map>

#include "game/messenger/MessengerUser.h"
#include "communication/outgoing/MessageComposer.h"

class FriendsListMessageComposer : public MessageComposer {

public:
    FriendsListMessageComposer(const std::map<int, MessengerUser*> friends) : 
        friends(friends) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(1);
        response.writeInt(0);
        response.writeInt(this->friends.size());

        for (auto friend_ : this->friends) {
            friend_.second->serialise(response, false);
        }
        
        return response;
    }

    const int getHeader() const {
        return Outgoing::InitMessengerMessageComposer;
    }

private:
    const std::map<int, MessengerUser*> friends;
};