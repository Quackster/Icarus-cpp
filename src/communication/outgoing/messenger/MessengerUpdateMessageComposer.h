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

#include "game/messenger/MessengerUser.h"
#include "communication/outgoing/MessageComposer.h"

class MessengerUpdateMessageComposer : public MessageComposer {

public:
    MessengerUpdateMessageComposer(MessengerUser *messenger_user, const bool force_offline) :
        messenger_user(messenger_user),
        force_offline(force_offline) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(0);
        response.writeInt(1);
        response.writeInt(0);
        messenger_user->serialiseUpdate(response, force_offline);
        response.writeInt(0);
        return response;
    }

    const int getHeader() const {
        return Outgoing::FriendUpdateMessageComposer;
    }

private:
    MessengerUser *messenger_user;
    bool force_offline;
};