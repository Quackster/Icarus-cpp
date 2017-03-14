
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

class RemoveItemMessageComposer : public MessageComposer {

public:
	RemoveItemMessageComposer(Item *item) :
		item(item) { }

	const Response compose() const {
		Response response = this->createResponse();

		response.writeString(item->id);
		response.writeBool(false);
		response.writeInt(item->user_id);

		if (item->isFloorItem()) {
			response.writeInt(0);
		}

		return response;
	}

	const int getHeader() const {
		return Outgoing::RemoveItemMessageComposer;
	}

private:
	Item *item;
};