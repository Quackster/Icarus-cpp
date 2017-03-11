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
	CataloguePageMessageComposer(CataloguePage catalogue_page, std::string type) :
		catalogue_page(catalogue_page),
		type(type) { }

	const Response compose() const {
		Response response = this->createResponse();

		response.writeInt(catalogue_page.id);
		response.writeString(type);
		response.writeString(catalogue_page.layout);
		response.writeInt(catalogue_page.headers.size());

		for (std::string header : catalogue_page.headers) {
			response.writeString(header);
		}

		response.writeInt(catalogue_page.texts.size());

		for (std::string text : catalogue_page.texts) {
			response.writeString(text);
		}

		if (catalogue_page.layout == "frontpage4" || catalogue_page.layout == "club_buy" || catalogue_page.layout == "guilds") {
			response.writeInt(0);
		}
		else {
			response.writeInt(0);
		}

		response.writeInt(0);
		response.writeBool(false);


		return response;
	}

	const int getHeader() const {
		return Outgoing::CataloguePageMessageComposer;
	}

private:
	std::string type;
	CataloguePage catalogue_page;
};