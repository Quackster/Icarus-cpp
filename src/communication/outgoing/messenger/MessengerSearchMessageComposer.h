/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>

#include "game/player/Player.h"
#include "game/messenger/MessengerUser.h"
#include "communication/outgoing/MessageComposer.h"

class MessengerSearchMessageComposer : public MessageComposer {

public:
    MessengerSearchMessageComposer(Player *player, std::vector<int> search) :
        player(player),
        search(search) { }

    const Response compose() const {
        Response response = this->createResponse();

        std::vector<MessengerUser> friends;
        std::vector<MessengerUser> strangers;

        for (int id : search) {
           if (id != player->getDetails()->id) {
                if (player->getMessenger()->isFriend(id)) {
                    friends.push_back(MessengerUser(id));
                }
                else {
                    strangers.push_back(MessengerUser(id));
                }
            }
        }

        response.writeInt(friends.size());

        for (MessengerUser friend_ : friends) {
            friend_.serialiseSearch(response);
        }

        response.writeInt(strangers.size());
        for (MessengerUser stranger : strangers) {
            stranger.serialiseSearch(response);
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::MessengerSearchMessageComposer;
    }

private:
    Player *player;
    std::vector<int> search;
};