/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include <iostream>

#include "game/player/PlayerDetails.h"

/*
    Constructor for session details

    Sets everything to a value specified
*/
PlayerDetails::PlayerDetails(int id, std::string username, std::string motto, std::string figure, int rank, int credits) :
    id(id), 
    username(username), 
    motto(motto), 
    figure(figure), 
    rank(rank), 
    credits(credits) { }

/*
    Deconstructor for session details
*/
PlayerDetails::~PlayerDetails() { }