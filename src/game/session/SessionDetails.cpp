#include "stdafx.h"

#include "game/session/SessionDetails.h"

/*
    Constructor for session details

    Sets everything to a value specified
*/
SessionDetails::SessionDetails(int id, std::string username, std::string motto, std::string figure, int rank, int credits) :
    id(id), username(username), motto(motto), figure(figure), rank(rank), credits(credits) {
}

/*
    Deconstructor for session details
*/
SessionDetails::~SessionDetails() {

}