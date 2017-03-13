/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/item/Item.h"
#include "misc/Utilities.h"

#include "communication/outgoing/MessageComposer.h"

class InventoryMessageComposer : public MessageComposer {

public:
	InventoryMessageComposer(std::vector<Item*> floor_items, std::vector<Item*> wall_items) :
		floor_items(floor_items),
		wall_items(wall_items) { }

	const Response compose() const {
		Response response = this->createResponse();
		response.writeInt(1);
		response.writeInt(0);

		response.writeInt(this->wall_items.size() + this->floor_items.size());

		for (Item *item : this->wall_items) {

			response.writeInt(item->id);
			response.writeString(Utilities::uppercase(item->getDefinition()->type));
			response.writeInt(item->id);
			response.writeInt(item->getDefinition()->sprite_id);

			if (Utilities::contains(item->getDefinition()->item_name, "landscape"))
				response.writeInt(4);
			else if (Utilities::contains(item->getDefinition()->item_name, "wallpaper"))
				response.writeInt(2);
			else if (Utilities::contains(item->getDefinition()->item_name, "a2"))
				response.writeInt(3);
			else
				response.writeInt(1);

			response.writeInt(0);
			response.writeString(item->extra_data);
			response.writeBool(item->getDefinition()->allow_recycle);
			response.writeBool(item->getDefinition()->allow_trade);
			response.writeBool(item->getDefinition()->allow_inventory_stack);
			response.writeBool(item->getDefinition()->allow_marketplace_sell);
			response.writeInt(-1);
			response.writeBool(false);
			response.writeInt(-1);
		}

		for (Item *item : this->floor_items) {
			response.writeInt(item->id);
			response.writeString(Utilities::uppercase(item->getDefinition()->type));
			response.writeInt(item->id);
			response.writeInt(item->getDefinition()->sprite_id);

			std::string interaction = item->getDefinition()->interaction_type;

			if (interaction == "group_item" ||
				interaction == "group_gate") {
				response.writeInt(17);
			} else if (interaction == "music_") {
				response.writeInt(8);
			}
			else {
				response.writeInt(1);
			}

			response.writeInt(0);
			response.writeString(item->extra_data);
			response.writeBool(item->getDefinition()->allow_recycle);
			response.writeBool(item->getDefinition()->allow_trade);
			response.writeBool(item->getDefinition()->allow_inventory_stack);
			response.writeBool(item->getDefinition()->allow_marketplace_sell);
			response.writeInt(-1);
			response.writeBool(false);
			response.writeInt(-1);
			response.writeString("");
			response.writeInt(0);
		}

		return response;
	}

	const int getHeader() const {
		return Outgoing::InventoryMessageComposer;
	}

private:
	std::vector<Item*> floor_items;
	std::vector<Item*> wall_items;
};