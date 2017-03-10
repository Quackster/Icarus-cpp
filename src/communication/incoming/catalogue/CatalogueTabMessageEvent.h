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
#include "game/catalogue/CatalogueTab.h"

#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/catalogue/CatalogueTabMessageComposer.h"

class CatalogueTabMessageEvent : public MessageEvent {

public:
	CatalogueTabMessageEvent() { }

    void handle(Player *player, Request &request) {

		std::string type = request.readString();

		std::vector<CatalogueTab> parent_tabs = Icarus::getGame()->getCatalogueManager()->getParentTabs(player->getDetails()->rank);

		if (parent_tabs.size() == 0) {
			cout << "oh noes its retarded" << endl;
			return;
		}

		player->send(CatalogueTabMessageComposer(type, parent_tabs, -1, player->getDetails()->rank));
    }
};