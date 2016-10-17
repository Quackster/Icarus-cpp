/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/player/PlayerDetails.h"

class Player;
class MessengerUser {

private:
    int user_id;
    PlayerDetails details;
    Player *session;


public:
    MessengerUser(int user_id);
    ~MessengerUser();
    void update();
    void serialise(Response &response, bool force_offline);
    bool inRoom();

    PlayerDetails getDetails() { return details; };
    bool isOnline() { return session != nullptr; }
};