#pragma once
#include "boot\Icarus.h"
#include "communication/outgoing/MessageComposer.h"

class NavigatorMetaDataComposer : public MessageComposer {

public:
    NavigatorMetaDataComposer() { }

    Response compose() {

        auto parent_tabs = Icarus::getGame()->getNavigatorManager()->getParentTabs();
        Response response = this->createResponse();
        response.writeInt((int)parent_tabs.size());

        for (auto tab : parent_tabs) {
            response.writeString(tab->getTabName());
            response.writeInt(0);
        } 
        return response;
    }

    int getHeader() {
        return Outgoing::NavigatorMetaDataComposer;
    }
};