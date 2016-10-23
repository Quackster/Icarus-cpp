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

#include "communication/outgoing/MessageComposer.h"

class MessengerCategoriesMessageComposer : public MessageComposer {

public:
    MessengerCategoriesMessageComposer() { }

    /*public static final int MAX_FRIENDS_DEFAULT = 300;
    public static final int MAX_FRIENDS_BASIC = 800;
    public static final int MAX_FRIENDS_VIP = 1000;*/

    const Response compose() const {
        Response response = this->createResponse();
        //response.writeInt(300);
        response.writeInt(300);
        response.writeInt(800);
        response.writeInt(1000);
        response.writeInt(0);
        return response;
    }

    const int getHeader() const {
        return Outgoing::MessengerCategoriesMessageComposer;
    }
};