#include "stdafx.h"
#include "game/session/Session.h"
#include "game/session/SessionManager.h"

/*
Constructor for Session Manager

Initialises the map for storing sessions along with their connection ID
*/
SessionManager::SessionManager() : 
    sessions(new std::map<int, Session*>()) {
}

/*
Deconstructor for Session Manager

Deletes all pointer variables
*/
SessionManager::~SessionManager() {

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
void SessionManager::addSession(Session *session, int connection_id) {

    if (!this->sessions->count(connection_id)) {
        this->sessions->insert(std::make_pair(connection_id, session));
    }
}

/*
Removes session from map if their connection ID exists

@param connectionID integer
@return none
*/
void SessionManager::removeSession(int connection_id) {

    if (this->sessions->count(connection_id)) {

        // Find session to delete
        Session *session = this->getSession(connection_id);

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
bool SessionManager::containsSession(int connection_id) {
    return this->sessions->count(connection_id) == 1 ? true : false;
}

/*
Returns the session from the map if their connection ID exists, will return NULL if
the session doesn't exist

@param connectionID integer
@return Session* instance
*/
Session *SessionManager::getSession(int connection_id) {

    if (this->sessions->count(connection_id)) {
        return this->sessions->find(connection_id)->second;
    }
    else {
        return nullptr;
    }
}