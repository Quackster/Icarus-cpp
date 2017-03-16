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

Item::Item(int id, int user_id, int owner_id, int item_id, int room_id, std::string x, std::string y, double z, int rotation, std::string extra_data) :
	id(id),
	user_id(user_id),
	owner_id(owner_id),
	item_id(item_id),
	room_id(room_id), 
	extra_data(extra_data) {

	this->owner_name = UserDao::getDetails(this->owner_id)->username;
	this->item_definition = Icarus::getGame()->getItemManager()->getDefinitionByID(this->item_id);

	if (x.length() > 0 && y.length() > 0) {
		if (this->isFloorItem()) {
			this->x = stoi(x);
			this->y = stoi(y);
			this->z = z;
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

void Item::updateEntities() {

	std::vector<Entity*> affected_players;

	Room *room = Icarus::getGame()->getRoomManager()->getRoom(this->room_id);

	if (room == nullptr) {
		return;
	}

	for (auto kvp : room->getEntities()) {

		Entity *entity = kvp.second;

		if (entity->getRoomUser()->current_item != nullptr) {
			if (entity->getRoomUser()->current_item->id == this->id) {

				if (!hasEntityCollision(entity->getRoomUser()->position.x, entity->getRoomUser()->position.y)) {
					entity->getRoomUser()->current_item = nullptr;
				}

				affected_players.push_back(entity);
			}

		}
		
		// Moved item inside a player
		else if (hasEntityCollision(entity->getRoomUser()->position.x, entity->getRoomUser()->position.y)) {
			entity->getRoomUser()->current_item = this;
			affected_players.push_back(entity);
		}
	}

	for (Entity *entity : affected_players) {
		entity->getRoomUser()->currentItemTrigger();
	}
}

bool Item::hasEntityCollision(int x, int y) {

	if (this->x == x && this->y == y) {
		return true;
	}
	else {

		for (auto kvp : this->getAffectedTiles()) {

			if (kvp.second.x == x && kvp.second.y == y) {
				return true;
			}
		}
	}

	return false;
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

/*
	Returns all tiles that are affected by the item (like beds, fences, etc)

	@param none
	@return map with counter as key, and affected tile position as value
*/
std::map<int, Position> Item::getAffectedTiles()
{
	int x = 0;

	std::map<int, Position> point_list;

	if (this->item_definition->length > 1) {
		if (rotation == 0 || rotation == 4) {
			for (int i = 1; i < this->item_definition->length; i++) {

				point_list.insert(std::make_pair(x++, Position(this->x, this->y + i, i)));

				for (int j = 1; j < this->item_definition->width; j++) {
					point_list.insert(std::make_pair(x++, Position(this->x + j, this->y + i, (i < j) ? j : i)));
				}
			}
		}
		else if (rotation == 2 || rotation == 6) {
			for (int i = 1; i < this->item_definition->length; i++) {
				point_list.insert(std::make_pair(x++, Position(this->x + i, this->y, i)));

				for (int j = 1; j < this->item_definition->width; j++) {
					point_list.insert(std::make_pair(x++, Position(this->x + i, this->y + j, (i < j) ? j : i)));
				}
			}
		}
	}

	if (this->item_definition->width > 1) {
		if (rotation == 0 || rotation == 4) {
			for (int i = 1; i < this->item_definition->width; i++) {
				point_list.insert(std::make_pair(x++, Position(this->x + i, this->y, i)));

				for (int j = 1; j < this->item_definition->length; j++) {
					point_list.insert(std::make_pair(x++, Position(this->x + i, this->y + j, (i < j) ? j : i)));
				}
			}
		}
		else if (rotation == 2 || rotation == 6) {
			for (int i = 1; i < this->item_definition->width; i++) {
				point_list.insert(std::make_pair(x++, Position(this->x, this->y + i, i)));

				for (int j = 1; j < this->item_definition->length; j++) {
					point_list.insert(std::make_pair(x++, Position(this->x + j, this->y + i, (i < j) ? j : i)));
				}
			}
		}
	}

	return point_list;
}

/*
	Serialise item for packet appending, this is used in almost everything when it comes to 
	handling items

	@param response reference
	@return nothing
*/
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

	}

	if (this->isFloorItem()) {

		response.writeInt(this->id);
		response.writeInt(this->item_definition->sprite_id);
		response.writeInt(this->x);
		response.writeInt(this->y);
		response.writeInt(this->rotation);
		response.writeString(this->z);
		response.writeString("");

		if (this->item_definition->interaction_type == "youtubetv") {

		}
		else {
			response.writeInt(1);
			response.writeInt(0);
			response.writeString(this->item_definition->interaction_type != "fbgate" ? this->extra_data : "");
		}

	}
		response.writeInt(-1); // secondsToExpiration
		response.writeInt((this->item_definition->interaction_modes_count > 0) ? 1 : 0);
		response.writeInt(this->owner_id); // owner id!
	}

/*
	Deconstructor for Item
*/
Item::~Item() { }
