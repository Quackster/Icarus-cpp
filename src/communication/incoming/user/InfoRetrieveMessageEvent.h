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
#include "communication/outgoing/user/CreditsMessageComposer.h"
#include "communication/outgoing/user/UserObjectMessageComposer.h"
#include "communication/outgoing/user/SendPerkAllowancesMessageComposer.h"

class InfoRetrieveMessageEvent : public MessageEvent {

public:
    InfoRetrieveMessageEvent() { }

    void handle(Player *player, Request &request) {

        player->send(UserObjectMessageComposer(player));
        player->send(SendPerkAllowancesMessageComposer());

        /*std::vector<Player*> hall_of_fame;
        
        for (int i = 0; i < 10; i++) {
            hall_of_fame.push_back(player);
        }

        Response res(Outgoing::CommunityGoalHallOfFameWidget);
        res.writeString("africaDesert");
        res.writeInt(hall_of_fame.size());

        int points = 10;
        int rank = 10;

        for (Player *winner : hall_of_fame) {
            res.writeInt(winner->getDetails()->id);
            res.writeString(winner->getDetails()->username);
            res.writeString(winner->getDetails()->figure);
            res.writeInt(rank--);
            res.writeInt(points--); // Number of points
        }

        player->getNetworkConnection()->send(res);*/

        Response res(3015);
        res.writeInt(2);
        res.writeInt(0);//ID
        res.writeString("Hello");//Title
        res.writeString("I bet you saw this boring landing page, didn't you?");//Text
        res.writeString("Click this?");//Button text
        res.writeInt(3);//Link type 0 and 3
        res.writeString("http://localhost/");//Link to article
        res.writeString("web_promo_small/laptop_habbo.png");//Image link

                                                            //stories_hallofselfies_teaser.png

        res.writeInt(1);//ID
        res.writeString("Boring one");//Title
        res.writeString("Look, here's another boring one!");//Text
        res.writeString("Click this?");//Button text
        res.writeInt(0);//Link type 0 and 3
        res.writeString("http://localhost/");//Link to article
        res.writeString("web_promo_small/stories_hallofselfies_teaser.png");//Image link

        player->getNetworkConnection()->send(res);
    }
};