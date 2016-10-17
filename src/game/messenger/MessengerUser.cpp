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
#include "dao/MessengerDao.h"
#include "game/messenger/MessengerUser.h"

MessengerUser::MessengerUser(int user_id) {


}

MessengerUser::~MessengerUser() {

}

void MessengerUser::update() {

}


void MessengerUser::serialise(Response &response, const bool force_offline) { }


bool MessengerUser::inRoom() {

    if (this->isOnline()) {
        return this->session->getRoomUser()->inRoom();
    }

    return false;
}