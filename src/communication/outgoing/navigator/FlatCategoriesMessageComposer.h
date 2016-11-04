/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>

#include "game/navigator/NavigatorCategory.h"
#include "communication/outgoing/MessageComposer.h"

class FlatCategoriesMessageComposer : public MessageComposer {

public:
    FlatCategoriesMessageComposer(std::vector<NavigatorCategory*> *categories, int rank) : 
        categories(categories), 
        rank(rank) {  }
    
    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->categories->size());

        for (auto category : *this->categories) {
            response.writeInt(category->id);
            response.writeString(category->name);
            response.writeBool(category->minimum_rank <= rank);
            response.writeBool(false);
            response.writeString("NONE");
            response.writeString("");
            response.writeBool(false);
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::FlatCategoriesMessageComposer;
    }

private:
    std::vector<NavigatorCategory*> *categories;
    int rank;

};