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

class PurchaseObjectMessageEvent : public MessageEvent {

public:
	PurchaseObjectMessageEvent() { }

	void handle(Player *player, Request &request) {

		int page_id = request.readInt();
		std::cout << "---------" << endl;
		int item_id = request.readInt();

		std::cout << "itemid: " << item_id << endl;

		/*int page_id = request.readInt();
		int item_id = request.readInt();
		std::string extra_data = request.readString();
		int price_amount = request.readInt();

		CataloguePage *page = Icarus::getGame()->getCatalogueManager()->getPage(page_id);

		if (page->minimum_rank > player->getDetails()->rank) {
			return;
		}

		std::cout << "itemid: " << item_id << endl;

		CatalogueItem *item = Icarus::getGame()->getCatalogueManager()->getItem(item_id);

		if (item == nullptr) {
			return;
		}

		int final_amount = price_amount;

		if (price_amount > 5) {

			int discount = (final_amount / 6);

			int free_items = (discount - 3) / 3;

			if (price_amount >= 42) {
				free_items++; // add another free item if more than 42 items 8)
			}

			if (price_amount >= 99) { // not divisible by 3
				free_items = 33;
			}

			final_amount = price_amount - free_items;
		}

		int amount_purchased = item->amount;

		if (item->item_definition->interaction_type == "teleport") {
			amount_purchased = 2;
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
			//session.send(new PurchaseErrorMessageComposer(creditsError, false));
			//std::cout << "PURCHASE BLOCKED REASON: 3" << std::endl;
			return;
		}

		// TODO: Seasonal currency error?

		if (item->cost_credits > 0) {
			player->getDetails()->setCredits(player->getDetails()->credits - item->cost_credits);
		}

		// TODO: Item badges
		// TODO: Limited sales update

		std::vector<Item*> bought;

		for (int i = 0; i < amount_purchased; i++) {
			//session.send(new PurchaseNotificationMessageComposer(item, finalAmount));

			Item *inventory_item = ItemDao::newItem(item->item_id, player->getDetails()->id, extra_data);
			bought.push_back(inventory_item);

			player->getInventory()->getItems().push_back(inventory_item);
		}

		/*session.send(new NewInventoryItemsMessageComposer(bought));
		session.send(new UpdateInventoryMessageComposer());*/
	}
};