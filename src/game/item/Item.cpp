/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include "stdafx.h"

#include "Item.h"

#include "dao/ItemDao.h"
#include "dao/UserDao.h"

#include "misc/Utilities.h"
#include "boot/Icarus.h"

/*
	Constructor for Item, this is a shared class between room and inventory items

	@param item id
	@param user id
	@param item definition id
	@param room id
	@param x coordinate
	@param y coordinate
	@param z coordinate
	@parm extradata
*/

Item::Item(int id,int user_id, int item_id, int room_id, int x, int y, double z, std::string extra_data) :
	id(id),
	user_id(user_id),
	item_id(item_id),
	room_id(room_id), 
	x(x), y(y), z(z),
	extra_data(extra_data) {

	this->owner_name = UserDao::getDetails(this->user_id)->username;
	this->item_definition = Icarus::getGame()->getItemManager()->getDefinitionByID(this->item_id);
}

/*
	Returns true if it's a wall item, false if it isn't

	@return boolean value
*/
bool Item::isWallItem() {

	if (this->item_definition->type == "e") {
		false;
	}

	return this->item_definition->type == "i";
}


/*
	Returns true if it's a floor item, false if it isn't

	@return boolean value
*/
bool Item::isFloorItem() {

	if (this->item_definition->type == "e") {
		false;
	}

	return this->item_definition->type == "s";
}

/*
	Save item details to database

	@return none
*/
void Item::save() {
	ItemDao::save(this);
}

/*
	Delete item from database

	@return none
*/
void Item::remove() {
	throw new std::exception("Not implemneted");
}

void Item::serialise(Response &response) {

	if (this->isWallItem()) {

		response.writeString(this->id + "");
		response.writeString(this->item_definition->sprite_id);
		response.writeString("");//this.getWallPosition());

		if (this->item_definition->interaction_type == "postit") {
			response.writeString(Utilities::split(this->extra_data, ' ')[0]);
		}
		else {
			response.writeString(this->extra_data);
		}

		response.writeString(-1);
		response.writeString(this->item_definition->interaction_type == "default" ? 0 : 1);
		response.writeString(this->user_id);

	}

	if (this->isFloorItem()) {

		response.writeString(this->id);
		response.writeString(this->item_definition->sprite_id);
		response.writeString(this->x);
		response.writeString(this->y);
		response.writeString(this->rotation);
		response.writeString(this->z);
		response.writeString(this->z);

		if (this->item_definition->interaction_type == "youtubetv") {

			response.writeString(0);
			response.writeString(1);
			response.writeString(1);
			response.writeString("THUMBNAIL_URL");
			response.writeString("/deliver/"/* + url*/);
		}
		else if (this->item_definition->interaction_type == "badgedisplay") {

			response.writeString(0);
			response.writeString(2);
			response.writeString(4);

			if (this->extra_data.length() > 0) {

				response.writeString("0"); // extradata check

				for (int i = 0; i <= Utilities::split(this->extra_data, (char)9).size() - 1; i++)
					response.writeString(Utilities::split(this->extra_data, (char)9)[i]);
			}
			else {
				response.writeString(0);
			}

		}
		else if (this->item_definition->interaction_type == "bg") {

			response.writeString(1); // is ads
			response.writeString(5); //type
			response.writeString(4);

			response.writeString(0); // online?
			response.writeString(0);
			response.writeString(0);
			response.writeString(0);
		}
		else if (this->item_definition->interaction_type == "mannequin") {

			std::vector<std::string> extra_datas = Utilities::split(this->extra_data, ';');

			if (Utilities::contains(this->extra_data, ";") && extra_datas.size() >= 3)
			{
				response.writeString(1);
				response.writeString(1);
				response.writeString(3);

				response.writeString("GENDER");
				response.writeString(extra_datas[0]);
				response.writeString("FIGURE");
				response.writeString(extra_datas[1]);
				response.writeString("OUTFIT_NAME");
				response.writeString(extra_datas[2]);
			}
			else
			{
				response.writeString(1);
				response.writeString(1);
				response.writeString(3);

				response.writeString("GENDER");
				response.writeString("m");
				response.writeString("FIGURE");
				response.writeString("");
				response.writeString("OUTFIT_NAME");
				response.writeString("");
			}
		}
		else {
			response.writeString((this->item_definition->interaction_type == "default") ? 0 : 1);
			response.writeString(0);
			response.writeString(this->extra_data);
		}

		response.writeString(-1); // secondsToExpiration
		response.writeString(this->item_definition->interaction_type == "default" ? 1 : 0);
		response.writeString(this->user_id); // owner id!
	}
}

/*
	Deconstructor for Item
*/
Item::~Item() { }
