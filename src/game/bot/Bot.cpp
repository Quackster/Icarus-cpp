/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "game/bot/Bot.h"

#include "boot/Icarus.h"

/*
    Session constructor

    @param NetworkConnection ptr
    @return session instance
*/
Bot::Bot(EntityDetails *details) : 
    details(details), 
    room_user(new RoomUser(this)) {

}


Bot::~Bot() {
    delete details;
    delete room_user;
}
