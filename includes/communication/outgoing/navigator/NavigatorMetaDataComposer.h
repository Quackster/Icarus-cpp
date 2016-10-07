#pragma once
#include "boot/Icarus.h"
#include "communication/outgoing/MessageComposer.h"

class NavigatorMetaDataComposer : public MessageComposer {

public:
    NavigatorMetaDataComposer() { }

    Response compose() {

        auto parentTabs = Icarus::getGame()->getNavigatorManager()->getParentTabs();
        Response response = this->createResponse();
        response.writeInt((int)parentTabs.size());

        for (auto tab : parentTabs) {
            response.writeString(tab->getTabName());
            response.writeInt(0);
        } 
        return response;
    }

    int getHeader() {
        return Outgoing::NavigatorMetaDataComposer;
    }
};