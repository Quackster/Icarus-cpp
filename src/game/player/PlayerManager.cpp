/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "game/player/PlayerManager.h"

/*
    Constructor for Session Manager

    Initialises the map for storing sessions along with their connection ID
*/
PlayerManager::PlayerManager() : 
    sessions(new std::map<int, Player*>()),
    authenticated_sessions(new std::map<int, Player*>()),
    authenticated_sessions_username(new std::map<std::string, Player*>()) {
}

/*
    Deconstructor for Session Manager

    Deletes all pointer variables
*/
PlayerManager::~PlayerManager() {

    for (auto pair : *sessions) {      
        delete pair.second; 
    }

    // Don't need to delete any pointers from authenticated_sessions
    //   as they share the same pointer with "sessions"

    // Delete sessions map
    delete sessions;
    delete authenticated_sessions;
    delete authenticated_sessions_username;
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

        if (session->getDetails() != nullptr) {
            this->authenticated_sessions->erase(session->getDetails()->id);
            this->authenticated_sessions_username->erase(session->getDetails()->username);
        }

        // Stop session from listening for more packets
        session->getNetworkConnection()->setConnectionState(false);

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
    return this->sessions->count(connection_id) == 1;
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

/*
    Gets player by user id, if it doesn't exist nullptr will be returned

    @param user id
    @return player ptr
*/
Player *PlayerManager::getPlayerById(int user_id) {

    if (this->authenticated_sessions->count(user_id)) {
        return this->authenticated_sessions->find(user_id)->second;
    }
    else {
        return nullptr;
    }
}

/*
    Gets player by username, if it doesn't exist nullptr will be returned

    @param username
    @return player ptr
*/
Player *PlayerManager::getPlayerByUsername(std::string username) {

    if (this->authenticated_sessions_username->count(username)) {
        return this->authenticated_sessions_username->find(username)->second;
    }
    else {
        return nullptr;
    }
}
