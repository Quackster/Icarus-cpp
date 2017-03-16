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

class FurniListNotificationComposer : public MessageComposer {

public:
	FurniListNotificationComposer(int item_id, int type) :
		item_id(item_id),
		type(type){ }

	const Response compose() const {
		Response response = this->createResponse();
		response.writeInt(1);
		response.writeInt(type);
		response.writeInt(1);
		response.writeInt(item_id);
		return response;
	}

	const int getHeader() const {
		return Outgoing::FurniListNotificationComposer;
	}

private:
	int item_id;
	int type;
};