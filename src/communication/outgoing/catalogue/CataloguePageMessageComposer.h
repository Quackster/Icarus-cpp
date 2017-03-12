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
		page(catalogue_page) { }

	const Response compose() const {
		
		CataloguePage &catalogue_page = *page;

		Response response = this->createResponse();

		response.writeInt(catalogue_page.id);
		response.writeString("NORMAL");
		response.writeString(catalogue_page.layout);

		response.writeInt(catalogue_page.images.size());
		for (auto image : catalogue_page.images) {
			response.writeString(image);
		}

		response.writeInt(catalogue_page.texts.size());
		for (auto text : catalogue_page.texts) {
			response.writeString(text);
		}

		if (catalogue_page.layout == "frontpage" || catalogue_page.layout == "club_buy" || catalogue_page.layout == "guilds") {
			response.writeInt(0);
		}
		else {
			
			response.writeInt(catalogue_page.items.size());

			for (CatalogueItem item : catalogue_page.items) {

				response.writeInt(item.id);
				response.writeString(item.catalogue_name);
				response.writeBool(false);

				if (item.cost_credits == 0 && item.cost_pixels == 0) {
					response.writeInt(item.cost_snow);
					response.writeInt(0);

				}
				else {
					response.writeInt(item.cost_credits);
					response.writeInt(item.cost_snow);
				}

				response.writeInt(item.achievement);

				if (item.limited_stack > 0 || item.data.type == "r") {
					response.writeBool(false);
				}
				else {
					response.writeBool(item.data.allow_gift);
				}

				response.writeInt(1); // is deal
				response.writeString(item.data.type);

				/*if (item.badge_id.length() > 0) {

					response.writeInt(this.badge);
					response.writeInt(this.subscriptionStatus);
					response.writeInt(this.amount);
				}
				else {*/

				response.writeInt(item.data.sprite_id);

				if (Utilities::contains(item.data.item_name, "_single_")) {
					response.writeString(Utilities::split(item.data.item_name, '_').at(2));
				}
				else {
					response.writeString(item.extra_data);
				}

				response.writeInt(item.amount);
				response.writeBool(item.limited_stack > 0);

				if (item.limited_stack > 0) {
					response.writeInt(item.limited_stack);
					response.writeInt(item.limited_sells);
				}

				response.writeInt(item.vip);

				if (item.limited_stack > 0) {
					response.writeBool(!(item.limited_stack > 0 && item.offer_active)); // && HaveOffer
				}
				else {
					response.writeBool(false);
				}
				//}

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
	CataloguePage *page;
};