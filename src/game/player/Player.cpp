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
#include "game/player/PlayerDetails.h"
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
    room_user(nullptr) {
    
    std::cout << " [SESSION] Client connected with ID: " << this->getNetworkConnection()->getConnectionId() << std::endl;
}

/*
    Initialise player and load their data

    @return none
*/
void Player::login() {

    /*
        Remove teh clones
    */
    if (Icarus::getPlayerManager()->getPlayers()->count(this->session_details->getId()) == 1) {
        //this->getNetworkConnection()->getSocket().close();
        return;
    }

    this->logged_in = true;

    /*
        Load player variables
    */
    this->room_user = new RoomUser(this);
    this->messenger = new Messenger(
        this->session_details->getId(), 
        MessengerDao::getFriends(this->session_details->getId()), 
        MessengerDao::getRequests(this->session_details->getId()));

    /*
        Cache room data
    */
    Icarus::getPlayerManager()->getPlayers()->insert(std::make_pair(this->session_details->getId(), this));
    Icarus::getGame()->getRoomManager()->createPlayerRooms(this->session_details->getId());
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
    Clear session of any responsibilities

    @return none
*/
void Player::clear() {
     
    // Can't continue clearing if session details is null...
    if (session_details == nullptr) {
        return;
    }

    if (this->logged_in) {

        Icarus::getPlayerManager()->getPlayers()->erase(this->session_details->getId());

        if (this->room_user != nullptr) {
            if (this->room_user->getRoom() != nullptr) {
                this->room_user->getRoom()->leave(this, false, true);
            }
        }

        std::vector<Room*> rooms = Icarus::getGame()->getRoomManager()->getPlayerRooms(this->session_details->getId()); {
            for (Room *room : rooms) {
                room->dispose();
            }
        }
    }
}

/*
    Session deconstructor, called when session disconnects, 
    is deleted from SessionManager class

    networkManager->connectionState has already been set to false 
    so there won't be any more packet receiving
*/
Player::~Player() {
    std::cout << " [SESSION] Client disconnected with ID: " << this->getNetworkConnection()->getConnectionId() << std::endl;

    if (messenger != nullptr) {
        messenger->sendStatus(true); // offline for everyone :'(
        delete messenger;
    }

    if (session_details != nullptr) {
        delete session_details;
    }

    if (room_user != nullptr) {
        delete room_user;
    }
}
