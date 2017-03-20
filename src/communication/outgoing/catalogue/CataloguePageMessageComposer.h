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

        response.writeInt(catalogue_page->items.size());

        for (CatalogueItem *item : catalogue_page->items) {
            item->serialise(response);
        }
        
        response.writeInt(0);
        response.writeBool(false);

        if (catalogue_page->layout == "frontpage4") {

            response.writeInt(4);

            response.writeInt(1);
            response.writeString("New Fitness Duck Bundle!");
            response.writeString("catalogue/feature_cata_vert_mallbundle3.png");
            response.writeInt(0);
            response.writeString("lympix16shop");
            response.writeInt(-1);

            response.writeInt(2);
            response.writeString("Clothes Shop");
            response.writeString("catalogue/feature_cata_hort_clothes.png");
            response.writeInt(0);
            response.writeString("clothing_top_picks");
            response.writeInt(-1);

            response.writeInt(3);
            response.writeString("The Icarus Pet Shop");
            response.writeString("catalogue/feature_cata_hort_pets.png");
            response.writeInt(0);
            response.writeString("pets_info");
            response.writeInt(-1);

            response.writeInt(4);
            response.writeString("Become a HC Member");
            response.writeString("catalogue/feature_cata_hort_HC_b.png");
            response.writeInt(0);
            response.writeString("hc_membership");
            response.writeInt(-1);

        }
        else {
            response.writeInt(0);
        }


        response.writeBool(false);
        
        return response;
    }

    const int getHeader() const {
        return Outgoing::CataloguePageMessageComposer;
    }

private:
    CataloguePage *catalogue_page;
};