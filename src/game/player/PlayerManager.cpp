#include "stdafx.h"

#include "game/player/PlayerManager.h"

/*
Constructor for Session Manager

Initialises the map for storing sessions along with their connection ID
*/
PlayerManager::PlayerManager() : 
    sessions(new std::map<int, Player*>()) {
}

/*
Deconstructor for Session Manager

Deletes all pointer variables
*/
PlayerManager::~PlayerManager() {

    for (auto pair : *sessions) {      
        delete pair.second; // Delete session pointer
    }

    // Empty out nullptr values
    this->sessions->clear();

    // Delete sessions map
    delete sessions;
}

/*
Adds a session to the map if their connection ID doesn't already exist

@param Session pointer
@param connectionID integer
*/
void PlayerManager::addSession(Player *player, int connection_id) {

    if (!this->sessions->count(connection_id)) {
        this->sessions->insert(std::make_pair(connection_id, player));
    }
}

/*
Removes session from map if their connection ID exists

@param connectionID integer
@return none
*/
void PlayerManager::removeSession(int connection_id) {

    if (this->sessions->count(connection_id)) {

        // Find session to delete
        Player *session = this->getSession(connection_id);

        // Remove session from map, remove it early to prevent any issues
        this->sessions->erase(connection_id);

        // Clear session of any responsibilites
        session->clear();

        // Clear session from memory
        delete session;
        
    }
}

/*
Checks whether or not the connection ID with session exists

@param connectionID integer
@return whether or not connection ID exists
*/
bool PlayerManager::containsSession(int connection_id) {
    return this->sessions->count(connection_id) == 1 ? true : false;
}

/*
Returns the session from the map if their connection ID exists, will return NULL if
the session doesn't exist

@param connectionID integer
@return Session* instance
*/
Player *PlayerManager::getSession(int connection_id) {

    if (this->sessions->count(connection_id)) {
        return this->sessions->find(connection_id)->second;
    }
    else {
        return nullptr;
    }
}