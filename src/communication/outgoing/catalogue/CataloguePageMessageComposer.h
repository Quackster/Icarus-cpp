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
	CataloguePageMessageComposer(CataloguePage catalogue_page) :
		catalogue_page(catalogue_page) { }

	const Response compose() const {
		Response response = this->createResponse();

		response.writeInt(catalogue_page.id);
		response.writeString("NORMAL");
		response.writeString(catalogue_page.layout);

		response.writeInt(this->catalogue_page.images->size());
		for (auto image : *this->catalogue_page.images) {
			response.writeString(image);
		}

		response.writeInt(this->catalogue_page.texts->size());
		for (auto text : *this->catalogue_page.texts) {
			response.writeString(text);
		}

		response.writeInt(0);
		response.writeInt(0);
/*
		cout << " Image size: " << catalogue_page.images->size() << endl;
		cout << " Text size: " << catalogue_page.texts->size() << endl;*/

		response.writeBool(false);

		return response;
	}

	const int getHeader() const {
		return Outgoing::CataloguePageMessageComposer;
	}

private:
	CataloguePage catalogue_page;
};