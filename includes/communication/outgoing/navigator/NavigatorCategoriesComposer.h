#pragma once
#include <vector>

#include "game/navigator/NavigatorCategory.h"
#include "communication/outgoing/MessageComposer.h"

class NavigatorCategoriesComposer : public MessageComposer {

public:
    NavigatorCategoriesComposer(vector<NavigatorCategory*> *categories) : categories(categories) {  }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(4 + ((int)categories->size()));

        for (auto category : *categories) {
            response.writeString("category__" + category->getName());
        }

        response.writeString("recommended");
        response.writeString("new_ads");
        response.writeString("staffpicks");
        response.writeString("official");
        return response;
    }

    int getHeader() {
        return Outgoing::NavigatorCategories;
    }

private:
    vector<NavigatorCategory*> *categories;

};