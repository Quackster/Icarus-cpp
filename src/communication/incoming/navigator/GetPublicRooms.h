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
#include "communication/outgoing/navigator/FlatCategoriesMessageComposer.h"
#include "communication/outgoing/navigator/NavigatorCategoriesComposer.h"
#include "communication/outgoing/navigator/NavigatorMetaDataComposer.h"
#include "communication/outgoing/navigator/NavigatorPreferencesMessageComposer.h"

#include "communication/outgoing/user/CreditsMessageComposer.h"
#include "communication/outgoing/user/UserObjectMessageComposer.h"
#include "communication/outgoing/user/SendPerkAllowancesMessageComposer.h"

class NewNavigatorMessageEvent : public MessageEvent {

public:
    NewNavigatorMessageEvent() { }

    void handle(Player *player, Request &request) {

        Response response(450); // "GB"

        response.writeInt(2); // category count

        response.writeInt(1337);
        response.writeString("Category Example 1");

        response.writeInt(9001);
        response.writeString("Category Example 2");

        response.writeInt(2);


        response.writeString("testing name");
        response.writeString("Awesome room description rite here m8");
        response.writeInt(1); // type??
        response.writeString("testing name");
        response.writeString("officialrooms_es/shoppingdeals_recroom.gif");
        response.writeInt(20); // users now

        int type = 3;
        response.writeInt(type); // public listing type

        if (type == 3) // if type is a room
        {
            response.writeString("officialrooms_es/shoppingdeals_recroom.gif");
            response.writeInt(-1);
            response.writeInt(0);
            response.writeString("hh_room_pub");
            response.writeInt(25); // max users
            response.writeInt(1001); // room id
        }

        response.writeString("another test");
        response.writeString("wow kewl!! xd");
        response.writeInt(0); // type??
        response.writeString("another test");
        response.writeString("officialrooms_defaults/hh_room_floatinggarden.png");
        response.writeInt(0);
        response.writeInt(10);
        response.writeInt(4);
        response.writeInt(227); // room id

        player->getNetworkConnection()->send(response);
    }
};