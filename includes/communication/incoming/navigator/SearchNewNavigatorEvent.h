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
#include "game/navigator/NavigatorTab.h"
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/navigator/SearchResultSetComposer.h"

class SearchNewNavigatorEvent : public MessageEvent {

public:
    SearchNewNavigatorEvent() { }

    void handle(Player *player, Request &request) {

        std::string tab = request.readString();
        std::string query = request.readString();

        NavigatorTab *navigator_tab = Icarus::getGame()->getNavigatorManager()->getTab(tab);

        if (navigator_tab == nullptr) {
            return;
        }

        player->send(SearchResultSetComposer(player, navigator_tab, query));
    }
};