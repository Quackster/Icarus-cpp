/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "dao/MessengerDao.h"
#include "boot/Icarus.h"

std::vector<MessengerUser*> *MessengerDao::getFriends(int user_id) {

    std::vector<MessengerUser*> *friends = new std::vector<MessengerUser*>();

    return friends;
}

std::vector<MessengerUser*> *getRequests(int user_id) {

    std::vector<MessengerUser*> *friends = new std::vector<MessengerUser*>();

    return friends;
}

std::vector<int> MessengerDao::search(std::string query) {

    std::vector<int> results;

    return results;
}

bool MessengerDao::newRequest(int fromId, int toId) {

    return true;
}

bool MessengerDao::removeRequest(int fromId, int toId) {

    return true;
}

bool MessengerDao::newFriend(int sender, int receiver) {

    return true;
}