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

#include "communication/outgoing/MessageComposer.h"

class NewInventoryItemsMessageComposer : public MessageComposer {

public:
	NewInventoryItemsMessageComposer(Item* item, int type) :
		item(item),
		type(type){ }

	const Response compose() const {
		Response response = this->createResponse();
		response.writeInt(1);
		response.writeInt(type);
		response.writeInt(1);
		response.writeInt(item->id);
		return response;
	}

	const int getHeader() const {
		return Outgoing::NewInventoryItemsMessageComposer;
	}

private:
	Item* item;
	int type;
};