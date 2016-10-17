/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "game/messenger/Messenger.h"

Messenger::Messenger(std::map<int, MessengerUser*> *friends, std::map<int, MessengerUser*> *requests) :
    friends(friends),
    requests(requests) { }

Messenger::~Messenger() { 
    
    for (auto friend_ : *this->friends) delete friend_.second;
    for (auto request : *this->requests) delete request.second;

    delete this->friends;
    delete this->requests;
}

MessengerUser *Messenger::getRequest(int user_id) { 

    if (this->friends->count(user_id)) {
        return this->friends->find(user_id)->second;
    }

    return nullptr;
}

MessengerUser *Messenger::getFriend(int user_id) { 

    if (this->requests->count(user_id)) {
        return this->requests->find(user_id)->second;
    }

    return nullptr;
}

bool Messenger::hasRequest(int id) { 
    return this->getRequest(id) != nullptr;
}

bool Messenger::isFriend(int id) {
    return this->getFriend(id) != nullptr;
}

void Messenger::removeFriend(int user_id) { }
void Messenger::sendStatus(bool force_offline) { }