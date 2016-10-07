#pragma once
#include <vector>

#include "game/session/Session.h"
#include "game/navigator/NavigatorTab.h"
#include "communication/outgoing/MessageComposer.h"

class SearchResultSetComposer : public MessageComposer {

public:
    SearchResultSetComposer(Session* session, NavigatorTab *tab, std::string query) : session(session), tab(tab), query(query) { }

    Response compose() {
        Response response = this->createResponse();

        response.writeString(tab->getTabName());
        response.writeString(query);

        if (query.length() == 0) {
            
            std::vector<NavigatorTab*> tabs;
            bool room_limit = true;

            if (tab->getChildId() != -1) {
                tabs.push_back(tab);
                room_limit = false;
            }
            else {
                auto child_tabs = tab->getChildTabs();
                tabs.insert(tabs.end(), child_tabs.begin(), child_tabs.end());
            }

            response.writeInt(tabs.size());

            for (auto navigator_tab : tabs) {
                response.writeString(navigator_tab->getTabName());
                response.writeString(navigator_tab->getTitle());

                if (room_limit) {
                    response.writeInt((int)navigator_tab->getButtonType());
                    response.writeBool(navigator_tab->getThumbnail());
                }
                else {
                    response.writeInt(2);
                    response.writeBool(false);
                }

                response.writeInt(navigator_tab->getThumbnail());
                response.writeInt(0);
            }
        }
        else {
            response.writeInt(0);
        }

        return response;
    }

    int getHeader() {
        return Outgoing::SearchResultSetComposer;
    }

private:
    Session* session;
    NavigatorTab *tab;
    std::string query;
};