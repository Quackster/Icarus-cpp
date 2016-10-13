/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/player/Player.h"

#include <iostream>
#include <map>

class PlayerManager 
{

public:
    PlayerManager();
    ~PlayerManager();
    void addSession(Player *session, int connection_id);
    void removeSession(int connection_id);
    bool containsSession(int connection_id);
    Player *getSession(int connection_id);
    Player *getPlayerById(int user_id);

    std::map<int, Player*> *getPlayers() { return this->authenticated_sessions; }

private:
    std::map<int, Player*> *sessions;
    std::map<int, Player*> *authenticated_sessions;

};