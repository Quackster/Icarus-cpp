/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include <sstream>

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

Item::Item(int id,int user_id, int item_id, int room_id, std::string x, std::string y, double z, int rotation, std::string extra_data) :
	id(id),
	user_id(user_id),
	item_id(item_id),
	room_id(room_id), 
	extra_data(extra_data) {

	this->owner_name = UserDao::getDetails(this->user_id)->username;
	this->item_definition = Icarus::getGame()->getItemManager()->getDefinitionByID(this->item_id);

	if (x.length() > 0 && y.length() > 0) {
		if (this->isFloorItem()) {
			this->x = stoi(x);
			this->y = stoi(y);
			this->rotation = rotation;

			//cout << "coordinates: " << this->x << ", " << this->y;
		}
		else {
			std::vector<std::string> x_data = Utilities::split(x, ',');

			this->side = x_data[0].c_str()[0];
			this->width_x = stoi(x_data[1]);
			this->width_y = stoi(x_data[2]);

			std::vector<std::string> y_data = Utilities::split(y, ',');

			this->length_x = stoi(y_data[0]);
			this->length_y = stoi(y_data[1]);

		}
	}
}

std::string Item::getWallPosition() {

	if (!this->isWallItem()) {
		return std::string();
	}

	std::stringstream ss;
	ss << ":w=" << this->width_x << "," << this->width_y << " " << "l=" << this->length_x << "," << this->length_y << " " << this->side;
	return ss.str();
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

}

void Item::serialise(Response &response) {

	if (this->isWallItem()) {

		response.writeString(this->id);
		response.writeInt(this->item_definition->sprite_id);
		response.writeString(this->getWallPosition());

		if (this->item_definition->interaction_type == "postit") {
			response.writeString(Utilities::split(this->extra_data, ' ')[0]);
		}
		else {
			response.writeString(this->extra_data);
		}

		response.writeInt(-1);
		response.writeInt(this->item_definition->interaction_type == "default" ? 0 : 1);
		response.writeInt(this->user_id);

	}

	if (this->isFloorItem()) {

		response.writeInt(this->id);
		response.writeInt(this->item_definition->sprite_id);
		response.writeInt(this->x);
		response.writeInt(this->y);
		response.writeInt(this->rotation);
		response.writeString(this->z);
		response.writeString(this->z);

		if (this->item_definition->interaction_type == "youtubetv") {

			response.writeInt(0);
			response.writeInt(1);
			response.writeInt(1);
			response.writeString("THUMBNAIL_URL");
			response.writeString("/deliver/"/* + url*/);
		}
		else if (this->item_definition->interaction_type == "badgedisplay") {

			response.writeInt(0);
			response.writeInt(2);
			response.writeInt(4);

			if (this->extra_data.length() > 0) {

				response.writeString("0"); // extradata check

				for (int i = 0; i <= Utilities::split(this->extra_data, (char)9).size() - 1; i++)
					response.writeString(Utilities::split(this->extra_data, (char)9)[i]);
			}
			else {
				response.writeInt(0);
			}

		}
		else if (this->item_definition->interaction_type == "bg") {

			response.writeInt(1); // is ads
			response.writeInt(5); //type
			response.writeInt(4);

			response.writeInt(0); // online?
			response.writeInt(0);
			response.writeInt(0);
			response.writeInt(0);
		}
		else if (this->item_definition->interaction_type == "mannequin") {

			std::vector<std::string> extra_datas = Utilities::split(this->extra_data, ';');

			if (Utilities::contains(this->extra_data, ";") && extra_datas.size() >= 3)
			{
				response.writeInt(1);
				response.writeInt(1);
				response.writeInt(3);

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
			response.writeInt((this->item_definition->interaction_type == "default") ? 0 : 1);
			response.writeInt(0);
			response.writeString(this->extra_data);
		}

		response.writeInt(-1); // secondsToExpiration
		response.writeInt(this->item_definition->interaction_type == "default" ? 1 : 0);
		response.writeInt(this->user_id); // owner id!
	}
}

/*
	Deconstructor for Item
*/
Item::~Item() { }
