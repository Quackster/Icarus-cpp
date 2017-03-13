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

#include "game/item/Item.h"
#include "game/catalogue/CataloguePage.h"

#include "communication/incoming/MessageEvent.h"

#include "dao/ItemDao.h"

#include "communication/outgoing/catalogue/PurchaseErrorMessageComposer.h"
#include "communication/outgoing/catalogue/PurchaseNotificationMessageComposer.h"

#include "communication/outgoing/item/NewInventoryItemsMessageComposer.h"
#include "communication/outgoing/item/UpdateInventoryMessageComposer.h"

class PurchaseObjectMessageEvent : public MessageEvent {

public:
	PurchaseObjectMessageEvent() { }

	void handle(Player *player, Request &request) {

		int page_id = request.readInt();
		int item_id = request.readInt();
		std::string extra_data = request.readString();
		int price_amount = request.readInt();

		CataloguePage *page = Icarus::getGame()->getCatalogueManager()->getPage(page_id);

		if (page->minimum_rank > player->getDetails()->rank) {
			return;
		}

		CatalogueItem *item = Icarus::getGame()->getCatalogueManager()->getItem(item_id);

		if (item == nullptr) {
			return;
		}

		int final_amount = item->amount;

		if (item->item_definition->interaction_type == "teleport") {
			final_amount = 2;
		}

		//TODO: Check for club membership

		if (item->limited_stack > 0 && item->limited_stack <= item->limited_sells) {
			// TODO: Alert deal soldout
			return;
		}

		if (item->limited_stack > 0) {

			// TODO: Allow possible chance that everyone is allowed to buy one rare
		}

		bool credits_error = false;

		// TODO: Pixel error
		if (player->getDetails()->credits < (item->cost_credits * final_amount)) {
			player->send(PurchaseErrorMessageComposer(credits_error, false));
			return;
		}

		// TODO: Seasonal currency error?

		if (item->cost_credits > 0) {
			player->getDetails()->setCredits(player->getDetails()->credits - (item->cost_credits * final_amount));
		}

		// TODO: Item badges
		// TODO: Limited sales update

		cout << "ITEM AMOUNT: " << item->amount << endl;

		std::vector<Item*> bought;

		for (int i = 0; i < final_amount; i++) {

			Item *inventory_item = ItemDao::newItem(item->item_id, player->getDetails()->id, extra_data);
			bought.push_back(inventory_item);

			player->send(NewInventoryItemsMessageComposer(inventory_item, 1));

			player->getInventory()->getItems().push_back(inventory_item);
		}

		player->send(PurchaseNotificationMessageComposer(item, final_amount));
		player->send(UpdateInventoryMessageComposer());
	}
};