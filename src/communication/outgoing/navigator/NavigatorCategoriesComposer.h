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

class NavigatorCategoriesComposer : public MessageComposer {

public:
    NavigatorCategoriesComposer(std::vector<NavigatorCategory*> categories) : 
        categories(categories) {  }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(4 + ((int)categories.size()));

        for (auto category : categories) {
            response.writeString("category__" + category->name);
        }

        response.writeString("recommended");
        response.writeString("new_ads");
        response.writeString("staffpicks");
        response.writeString("official");
        return response;
    }

    const int getHeader() const {
        return Outgoing::NavigatorCategories;
    }

private:
    std::vector<NavigatorCategory*> categories;

};