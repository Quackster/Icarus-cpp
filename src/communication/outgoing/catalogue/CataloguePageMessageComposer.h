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

class CataloguePageMessageComposer : public MessageComposer {

public:
	CataloguePageMessageComposer(CataloguePage *catalogue_page) :
		catalogue_page(catalogue_page) { }

	const Response compose() const {
		
		Response response = this->createResponse();

		response.writeInt(catalogue_page->id);
		response.writeString("NORMAL");
		response.writeString(catalogue_page->layout);

		response.writeInt(catalogue_page->images.size());
		for (auto image : catalogue_page->images) {
			response.writeString(image);
		}

		response.writeInt(catalogue_page->texts.size());
		for (auto text : catalogue_page->texts) {
			response.writeString(text);
		}

		if (catalogue_page->layout == "frontpage" || catalogue_page->layout == "club_buy" || catalogue_page->layout == "guilds") {
			response.writeInt(0);
		}
		else {
			
			response.writeInt(catalogue_page->items.size());

			for (CatalogueItem *item : catalogue_page->items) {

				response.writeInt(item->id);

				if (item->id == 1166) {

					/* (char)number & 0xff;
    output[2] = (char)(number >> 8) & 0xff;
    output[1] = (char)(number >> 16) & 0xff;
    output[0] = (char)(number >> 24) & 0xff*/

					int number = item->id;


					char output[4];

					output[3] = (char)number & 0xff;
					output[2] = (char)(number >> 8) & 0xff;
					output[1] = (char)(number >> 16) & 0xff;
					output[0] = (char)(number >> 24) & 0xff;

					std::cout << (int)output[0] << "/";
					std::cout << (int)output[1] << "/";
					std::cout << (int)output[2] << "/";
					std::cout << (int)output[3] << "/";
					std::cout << endl;
				}


				//std::cout << item->catalogue_name << " // " << item->id << endl;

				//gothic_sofa*3 // 1166
				//cout << item->id << endl;

				response.writeString(item->catalogue_name);
				response.writeBool(false);

				if (item->cost_credits == 0 && item->cost_pixels == 0) {
					response.writeInt(item->cost_snow);
					response.writeInt(0);

				}
				else {
					response.writeInt(item->cost_credits);
					response.writeInt(item->cost_snow);
				}

				response.writeInt(0); // Quest type

				if (item->limited_stack > 0 || item->item_definition->type == "r") {
					response.writeBool(false);
				}
				else {
					response.writeBool(item->item_definition->allow_gift);
				}

				response.writeInt(1);
				response.writeString(item->item_definition->type);
				response.writeInt(item->item_definition->sprite_id);

				if (Utilities::contains(item->catalogue_name, "_single_")) {
					response.writeString(Utilities::split(item->catalogue_name, '_').at(2));
				}
				else {
					response.writeString(item->extra_data);
				}

				response.writeInt(item->amount);
				response.writeBool(item->limited_stack > 0);

				if (item->limited_stack > 0) {
					response.writeInt(item->limited_stack);
					response.writeInt(item->limited_sells);
				}

				response.writeInt(item->vip);

				if (item->limited_stack > 0) {
					response.writeBool(!(item->limited_stack > 0 && item->offer_active)); // && HaveOffer
				}
				else {
					response.writeBool(false);
				}
			}
		}

		response.writeInt(0);
		response.writeBool(false);

		return response;
	}

	const int getHeader() const {
		return Outgoing::CataloguePageMessageComposer;
	}

private:
	CataloguePage *catalogue_page;
};