/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "game/player/Player.h"

#include "dao/UserDao.h"
#include "dao/MessengerDao.h"

#include "boot/Icarus.h"

/*
    Session constructor

    @param NetworkConnection ptr
    @return session instance
*/
Player::Player(NetworkConnection *network_connection) : 
    network_connection(network_connection), 
    session_details(nullptr), 
    room_user(nullptr),
    logged_in(false),
    disconnected(false) {
    
    if (Icarus::getLogConfiguration()->getBool("log.player.connect")) {
        std::cout << " [SESSION] Client connected with ID: " << this->getNetworkConnection()->getConnectionId() << std::endl;
    }
}

/*
    Initialise player and load their data

    @return none
*/
void Player::login() {

    /*
        Remove teh clones
    */
    if (Icarus::getPlayerManager()->getPlayersIDLookup()->count(this->session_details->id) == 1) {
        //this->getNetworkConnection()->getSocket().close();
        return;
    }

    this->logged_in = true;    
    
    /*
        Insert players into lookup dictionaries
    */
    Icarus::getPlayerManager()->getPlayersIDLookup()->insert(std::make_pair(this->session_details->id, this));
    Icarus::getPlayerManager()->getPlayersUsernameLookup()->insert(std::make_pair(this->session_details->username, this));

    /*
        Load player variables
    */
    this->room_user = new RoomUser(this);
    this->messenger = new Messenger(
        this,
        this->session_details->id, 
        MessengerDao::getFriends(this->session_details->id), 
        MessengerDao::getRequests(this->session_details->id));

    /*
        Cache room data
    */

    Icarus::getGame()->getRoomManager()->createPlayerRooms(this->session_details->id);
}

/*
    Returns true or not if player has certain permission

    @return bool
*/
bool Player::hasFuse(std::string fuse_right) {
    return false;
}

/*
    Save player details

    @return none
*/
void Player::save() {
    UserDao::updateUser(this->session_details->id, this->session_details);
}

/*
    Send message composer to the session's socket

    @param MessageComposer ptr
    @return none
*/
void Player::send(const MessageComposer &composer) {
    this->network_connection->send(composer);
}

/*
    Gets list of player rooms

    @return vector of room ptr
*/
std::vector<Room*> Player::getRooms() {
    return Icarus::getGame()->getRoomManager()->getPlayerRooms(this->session_details->id);
}

/*
    Clear session of any responsibilities

    @return none
*/
void Player::clear() {
     
    // Can't continue clearing if session details is null...
    if (session_details == nullptr) {
        return;
    }

    if (this->logged_in) {

        if (this->room_user != nullptr) {
            this->room_user->leaveRoom(false);
        }

        std::vector<Room*> rooms = Icarus::getGame()->getRoomManager()->getPlayerRooms(this->session_details->id); {
            for (Room *room : rooms) {
                room->dispose();
            }
        }
    }
}

/*
    Close connection
*/
void Player::close() {
    this->network_connection->setConnectionState(false);
    this->network_connection->getSocket().close();
}

/*
    Session deconstructor, called when session disconnects, 
    is deleted from SessionManager class

    networkManager->connectionState has already been set to false 
    so there won't be any more packet receiving
*/
Player::~Player() {

    this->getNetworkConnection()->setConnectionState(false);

    if (Icarus::getLogConfiguration()->getBool("log.player.disconnect")) {
        std::cout << " [SESSION] Client disconnected with ID: " << this->getNetworkConnection()->getConnectionId() << std::endl;
    }

    if (this->logged_in) {
        messenger->sendStatus(true); // offline for everyone :'(
    }

    delete messenger;
    delete session_details;
    delete room_user;
}
