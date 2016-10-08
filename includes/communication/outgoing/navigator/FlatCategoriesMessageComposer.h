#pragma once
#include <vector>

#include "game/navigator/NavigatorCategory.h"
#include "communication/outgoing/MessageComposer.h"

class FlatCategoriesMessageComposer : public MessageComposer {

public:
    FlatCategoriesMessageComposer(std::vector<NavigatorCategory*> *categories, int rank) : categories(categories), rank(rank) {  }
    
    Response compose() {
        Response response = this->createResponse();
        response.writeInt(this->categories->size());

        for (auto category : *this->categories) {
            response.writeInt(category->getId());
            response.writeString(category->getName());
            response.writeBool(category->getMinimumRank() <= rank);
            response.writeBool(false);
            response.writeString("NONE");
            response.writeString("");
            response.writeBool(false);
        }

        return response;
    }

    int getHeader() {
        return Outgoing::FlatCategoriesMessageComposer;
    }

private:
    std::vector<NavigatorCategory*> *categories;
    int rank;

};