#include "stdafx.h"
#include "Session.h"
#include "SessionManager.h"

/*
Constructor for Session Manager

Initialises the map for storing sessions along with their connection ID
*/
SessionManager::SessionManager() {
	this->sessions = new map<int, Session*>();
}

/*
Adds a session to the map if their connection ID doesn't already exist

@param Session pointer
@param connectionID integer
*/
void SessionManager::addSession(Session *session, int connectionID) {

	if (!this->sessions->count(connectionID)) {
		this->sessions->insert(std::make_pair(connectionID, session));
	}
}


/*
Removes session from map if their connection ID exists

@param connectionID integer
@return none
*/
void SessionManager::removeSession(int connectionID) {

	if (this->sessions->count(connectionID)) {

		// Find session to delete
		Session *session = this->getSession(connectionID);

		// Remove session from map
		this->sessions->erase(connectionID);

		// Clear session from memory
		delete session;
		
	}
}

/*
Checks whether or not the connection ID with session exists

@param connectionID integer
@return whether or not connection ID exists
*/
bool SessionManager::containsSession(int connectionID) {
	return this->sessions->count(connectionID) == 1 ? true : false;
}

/*
Returns the session from the map if their connection ID exists, will return NULL if
the session doesn't exist

@param connectionID integer
@return Session* instance
*/
Session *SessionManager::getSession(int connectionID) {

	if (this->sessions->count(connectionID)) {
		return this->sessions->find(connectionID)->second;
	}
	else {
		return NULL;
	}
}