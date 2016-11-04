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

#include "game/player/Player.h"
#include "game/navigator/NavigatorTab.h"
#include "communication/outgoing/MessageComposer.h"

class SearchResultSetComposer : public MessageComposer {

public:
    SearchResultSetComposer(Player* player, NavigatorTab *tab, std::string query) : 
        player(player), 
        tab(tab), 
        query(query) { }

    const Response compose() const {
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
                    response.writeInt(room_limit ? (int)navigator_tab->getButtonType() : 2); // force no button
                    response.writeBool(navigator_tab->getClosed()); // force collapsed
                }
                else {
                    response.writeInt(2);
                    response.writeBool(false);
                }

                response.writeInt(navigator_tab->getThumbnail());

                RoomPopulator *populator = Icarus::getGame()->getNavigatorManager()->getPopulator(navigator_tab->getPopulatorName());
                std::vector<Room*> rooms = populator->populate(room_limit, player);

                response.writeInt(rooms.size());

                for (Room *room : rooms) {
                    room->serialise(response);
                }
            }
        }
        else {
            response.writeInt(0);
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::SearchResultSetComposer;
    }

private:
    Player* player;
    NavigatorTab *tab;
    std::string query;
};