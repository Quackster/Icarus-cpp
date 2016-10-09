#include "stdafx.h"

#include "game/player/PlayerDetails.h"

/*
    Constructor for session details

    Sets everything to a value specified
*/
PlayerDetails::PlayerDetails(int id, std::string username, std::string motto, std::string figure, int rank, int credits) :
    id(id), username(username), motto(motto), figure(figure), rank(rank), credits(credits) {
}

/*
    Deconstructor for session details
*/
PlayerDetails::~PlayerDetails() {

}