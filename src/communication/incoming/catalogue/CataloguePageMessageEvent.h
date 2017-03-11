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
#include "communication/outgoing/catalogue/CataloguePageMessageComposer.h"

class CataloguePageMessageEvent : public MessageEvent {

public:
	CataloguePageMessageEvent() { }

    void handle(Player *player, Request &request) {

		int page_id = request.readInt();

		CataloguePage catalogue_page = Icarus::getGame()->getCatalogueManager()->getPage(page_id);

		if (catalogue_page.id == -1) {
			return;
		}

		player->send(CataloguePageMessageComposer(catalogue_page, "NORMAL"));
    }
};