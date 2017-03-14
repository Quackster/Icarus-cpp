/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "communication/outgoing/MessageComposer.h"
#include "game/item/Item.h"

class MoveItemMessageComposer : public MessageComposer {

public:
	MoveItemMessageComposer(Item *item) :
		item(item) { }

	const Response compose() const {
		Response response = this->createResponse();
		item->serialise(response);
		return response;
	}

	const int getHeader() const {
		return Outgoing::MoveItemMessageComposer;
	}

private:
	Item *item;
};