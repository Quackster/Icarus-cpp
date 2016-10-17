/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "game/player/Player.h"
#include "game/messenger/Messenger.h"
#include "communication/outgoing/messenger/MessengerUpdateMessageComposer.h"

/*
    Constructor for Messenger

    @param user id
    @param map of user ids and messenger user ptrs of which are friends
    @param map of user ids and messenger user ptrs of which are requests
*/
Messenger::Messenger(int user_id, std::map<int, MessengerUser*> *friends, std::map<int, MessengerUser*> *requests) :
    user_id(user_id),
    friends(friends),
    requests(requests) { }

/*
    Deconstructor for messenger
*/
Messenger::~Messenger() { 
    
    for (auto friend_ : *this->friends) delete friend_.second;
    for (auto request : *this->requests) delete request.second;

    delete this->friends;
    delete this->requests;
}

/*
    Get given request by user id, will return null if no request was found

    @return user id
    @return messenger user ptr
*/
MessengerUser *Messenger::getRequest(int user_id) { 

    if (this->friends->count(user_id)) {
        return this->friends->find(user_id)->second;
    }

    return nullptr;
}

/*
    Get given friend by user id, will return null if no friend was found

    @return user id
    @return messenger user ptr
*/
MessengerUser *Messenger::getFriend(int user_id) { 

    if (this->requests->count(user_id)) {
        return this->requests->find(user_id)->second;
    }

    return nullptr;
}

/*
    True or false depending if the user with the given id has sent a request or not

    @bool user id
    @return boolean
*/
bool Messenger::hasRequest(int id) { 
    return this->getRequest(id) != nullptr;
}

/*
    True or false depending if the user with the given id is a friend or not

    @bool user id
    @return boolean
*/
bool Messenger::isFriend(int id) {
    return this->getFriend(id) != nullptr;
}

void Messenger::removeFriend(int user_id) { }

/*
    Update player status to every online friend

    @bool force offline mode for friend (used when disconnecting)
    @return none
*/
void Messenger::sendStatus(bool force_offline) {

    const Response response = MessengerUpdateMessageComposer(std::make_unique<MessengerUser>(this->user_id).get(), force_offline).compose();

    for (auto kvp : *this->friends) {

        MessengerUser *friend_ = kvp.second;

        if (friend_->isOnline()) {
            friend_->getPlayer()->getNetworkConnection()->send(response);
        }
    }
}