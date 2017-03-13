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

Item::Item(int id,int user_id, int item_id, int room_id, int x, int y, int z, std::string extra_data) :
	id(id),
	user_id(user_id),
	item_id(item_id),
	room_id(room_id), 
	x(x), y(y), z(z),
	extra_data(extra_data) {

	this->item_definition = Icarus::getGame()->getItemManager()->getDefinitionByID(this->item_id);
}


/*
	Returns true if it's a wall item, false if it isn't

	@return boolean value
*/
bool Item::isWallItem() {
	return this->item_definition->type == "i";
}

/*
	Deconstructor for Item
*/
Item::~Item() { }
