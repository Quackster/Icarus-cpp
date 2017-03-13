/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>
#include "game/item/definitions/ItemDefinition.h"

class Response;
class CatalogueItem {

public:
    CatalogueItem();
    ~CatalogueItem();
	void serialise(Response &response);
	ItemDefinition *getDefinition() { return this->item_definition; }
	void setDefinition(ItemDefinition *definition) { this->item_definition = definition; }

	int id = -1;
	int page_id = -1;
	int item_id;
	std::string catalogue_name;
	int cost_credits;
	int cost_pixels;
	int cost_snow;
	int amount;
	int vip;
	int achievement;
	int song_id;
	int limited_sells;
	int limited_stack;
	bool offer_active;
	std::string extra_data;
	std::string badge_id;
	int flat_id;

private:
	ItemDefinition *item_definition = nullptr;

};