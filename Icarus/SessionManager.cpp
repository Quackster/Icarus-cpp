#include "stdafx.h"
#include "Session.h"
#include "SessionManager.h"


SessionManager::SessionManager() {
	this->sessions = new map<int, Session*>();
}

void SessionManager::addSession(Session *session, int connectionID) {

	if (!this->sessions->count(connectionID)) {
		this->sessions->insert(std::make_pair(connectionID, session));
	}
}

void SessionManager::removeSession(int connectionID) {

	if (this->sessions->count(connectionID)) {

		// Delete it??
		this->sessions->erase(connectionID);
	}
}

Session* SessionManager::getSession(int connectionID) {

	if (this->sessions->count(connectionID)) {
		return this->sessions->find(connectionID)->second;
	}
	else {
		return NULL;
	}
}