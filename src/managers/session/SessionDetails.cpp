#include "stdafx.h"
#include "managers/session/SessionDetails.h"

/*
    Constructor for session details

    Sets everything to a default value
*/
SessionDetails::SessionDetails() {
    this->id = -1;
    this->username = "";
    this->motto = "";
    this->figure = "";
    this->rank = 1;
    this->credits = 0;
    this->machine_id = "";
    this->authenticated = false;
}

/*
    Fill session details

    This method is called when a user logs in
*/
void SessionDetails::fill(int id, string username, string motto, string figure, int rank, int credits) {
    this->id = id;
    this->username = username;
    this->motto = motto;
    this->figure = figure;
    this->rank = rank;
}

/*
    Deconstructor for session details
*/
SessionDetails::~SessionDetails() {

}