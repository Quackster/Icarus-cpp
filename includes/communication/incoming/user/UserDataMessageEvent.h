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

#include "communication/outgoing/user/CreditsMessageComposer.h"
#include "communication/outgoing/user/UserObjectMessageComposer.h"
#include "communication/outgoing/user/SendPerkAllowancesMessageComposer.h"

class UserDataMessageEvent : public MessageEvent {

public:
    UserDataMessageEvent() { }

    void handle(Player *player, Request &request) {

        player->login();

        auto categories = Icarus::getGame()->getNavigatorManager()->getCategories();
        
        /*
        Enable new navigator
        */
        player->send(FlatCategoriesMessageComposer(categories, player->getDetails()->getRank()));
        player->send(NavigatorCategoriesComposer(categories));
        player->send(NavigatorMetaDataComposer());

        /*
        Send user data
        */
        player->send(CreditsMessageComposer(player->getDetails()->getCredits()));
        player->send(UserObjectMessageComposer(player));
        player->send(SendPerkAllowancesMessageComposer());

        Response res(2820);
        res.writeInt(2);
        res.writeInt(0);//Promotion.Id); //ID
        res.writeString("Hello");//Promotion.Title); //Title
        res.writeString("I bet you saw this boring landing page, didn't you?");//Promotion.Text); //Text
        res.writeString("Click this?");//Promotion.ButtonText); //Button text
        res.writeInt(3);//Promotion.ButtonType); //Link type 0 and 3
        res.writeString("http://localhost/");//Promotion.ButtonLink); //Link to article
        res.writeString("web_promo_small/laptop_habbo.png");//Promotion.ImageLink); //Image link

        //stories_hallofselfies_teaser.png

        res.writeInt(1);//Promotion.Id); //ID
        res.writeString("Boring one");//Promotion.Title); //Title
        res.writeString("Look, here's another boring one!");//Promotion.Text); //Text
        res.writeString("Click this?");//Promotion.ButtonText); //Button text
        res.writeInt(0);//Promotion.ButtonType); //Link type 0 and 3
        res.writeString("http://localhost/");//Promotion.ButtonLink); //Link to article
        res.writeString("web_promo_small/stories_hallofselfies_teaser.png");//Promotion.ImageLink); //Image link

        player->getNetworkConnection()->send(res);
    }
};