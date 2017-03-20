/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "CatalogueItem.h"

#include "communication/streams/Response.h"

#include "misc/Utilities.h"

/*
    Constructor for catalogue items
*/
CatalogueItem::CatalogueItem() { }

/*
    Serialise packet data for catalogue item

    @param response packet to serialise
    @return none
*/
void CatalogueItem::serialise(Response &response) {

    response.writeInt(this->id);

    response.writeString(this->catalogue_name);
    response.writeBool(false);

    if (this->cost_credits == 0 && this->cost_pixels == 0) {
        response.writeInt(this->cost_snow);
        response.writeInt(0);

    }
    else {
        response.writeInt(this->cost_credits);
        response.writeInt(this->cost_snow);
    }

    response.writeInt(0); // Quest type

    if (this->limited_stack > 0 || this->item_definition->type == "r") {
        response.writeBool(false);
    }
    else {
        response.writeBool(this->item_definition->allow_gift);
    }

    response.writeInt(1);
    response.writeString(this->item_definition->type);
    response.writeInt(this->item_definition->sprite_id);

    if (Utilities::contains(this->catalogue_name, "_single_")) {
        response.writeString(Utilities::split(this->catalogue_name, '_').at(2));
    }
    else {
        response.writeString(this->extra_data);
    }

    response.writeInt(this->amount);
    response.writeBool(this->limited_stack > 0);

    if (this->limited_stack > 0) {
        response.writeInt(this->limited_stack);
        response.writeInt(this->limited_sells);
    }

    response.writeInt(this->vip);

    if (this->limited_stack > 0) {
        response.writeBool(!(this->limited_stack > 0 && this->offer_active)); // && HaveOffer
    }
    else {
        response.writeBool(false);
    }

    response.writeBool(false);
    response.writeString("");
}

/*
    Deconstructor for catalogue item
*/
CatalogueItem::~CatalogueItem() { }