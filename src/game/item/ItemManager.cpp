/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include "stdafx.h"

#include "dao/FurnitureDao.h"

#include "ItemDefinition.h"
#include "ItemManager.h"

/*
	Constructor for Furniture
*/
ItemManager::ItemManager() :
	id_lookup(ItemDao::getItemDefinitions()) { 

	for (auto furniture : this->id_lookup) {
		this->sprite_lookup[furniture.first] = furniture.second;
	}
}

/*
	Get Furniture instance by sprite id

	@param sprite id
	@return furniture
*/
ItemDefinition *ItemManager::getDefinitionByID(int item_id) {

	if (this->id_lookup.count(item_id) > 0) {
		return this->id_lookup.find(item_id)->second;
	}

	return nullptr;
}

ItemDefinition *ItemManager::getDefinitionBySpriteID(int item_id) {

	if (this->sprite_lookup.count(item_id) > 0) {
		return this->sprite_lookup.find(item_id)->second;
	}


	return nullptr;
}

ItemManager::~ItemManager()
{
}
