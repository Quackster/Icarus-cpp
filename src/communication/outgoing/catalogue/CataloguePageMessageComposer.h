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
                item->serialise(response);
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