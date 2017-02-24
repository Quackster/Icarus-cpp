/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "communication/streams/Response.h"

class Player;
class MessengerUser {

private:
    int user_id;
    std::shared_ptr<EntityDetails> details;
    Player *session;


public:
    MessengerUser(int user_id);
    ~MessengerUser();

    void update();
    void serialise(Response &response, const bool force_offline);
    void serialiseSearch(Response &response);
    bool inRoom();

    Player *getPlayer() {
        return session;
    };

    std::shared_ptr<EntityDetails> getDetails() { return details; };
    bool isOnline() { this->update(); return session != nullptr; }

	bool visible_status;
};