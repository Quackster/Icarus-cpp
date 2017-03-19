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
#include "game/room/misc/RoomNewbie.h"
#include "game/messenger/MessengerUser.h"
#include "game/item/inventory/Inventory.h"
#include "game/item/Item.h"

#include "misc/Utilities.h"

#include "communication/outgoing/misc/BroadcastMessageAlertComposer.h"

#include "dao/UserDao.h"
#include "dao/RoomDao.h"
#include "dao/NavigatorDao.h"
#include "dao/MessengerDao.h"
#include "dao/ItemDao.h"

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

	if (network_connection == nullptr) {
		return;
	}
    
    if (Icarus::getLogConfiguration()->getBool("log.player.connect")) {
        cout << " [SESSION] Client connected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;
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
		this->getNetworkConnection()->getSocket().close();
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

	this->inventory = new Inventory(
		this, ItemDao::getInventoryItems(this->session_details->id));

	this->messenger_user = new MessengerUser(
		this->session_details->id);

	/*
		Cache room data
	*/
	Icarus::getGame()->getRoomManager()->createPlayerRooms(this->session_details->id);

	//
	// If this is the user's first time logging in, lets give them
	//   a starter room :-)
	//
	if (!this->session_details->has_logged_in) {
		this->handleNewPlayer();
	}

	this->save();
}

/*
	Server handling for new player

	@return none
*/
void Player::handleNewPlayer() {

	if (this->session_details->has_logged_in) {
		return;
	}

	this->session_details->has_logged_in = true;
	this->save();

	if (Icarus::getGameConfiguration()->getBool("newuser.create.newbie.room")) {

		std::vector<RoomNewbie*> newbie_rooms = Icarus::getGame()->getRoomManager()->getNewbieRoomTemplates();

		if (newbie_rooms.size() < 1) {
			return;
		}

		RoomNewbie *newbie_template = newbie_rooms.at(Icarus::getRandomNumber(0, newbie_rooms.size() - 1));

		int room_id = NavigatorDao::createRoom(
			this->session_details->username + "'s Room",
			"My first room",
			"model_newbie",
			this->session_details->id, 0, 30, 0);


		Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

		room->getData()->wallpaper = newbie_template->wallpaper;
		room->getData()->floor = newbie_template->floorpaper;
		room->save();

		for (RoomNewbieItem newbie_item : newbie_template->items) {

			ItemDefinition *definition = newbie_item.definition;

			Item *item = ItemDao::newItem(definition->id, this->session_details->id, "");
			item->room_id = room->id;

			if (newbie_item.x == -1) { // Wall item
				item->parseWallPosition(newbie_item.position);

			}
			else { // Floor item

				item->x = newbie_item.x;
				item->y = newbie_item.y;
				item->rotation = newbie_item.rotation;
				item->z = room->getDynamicModel()->getTileHeight(item->x, item->y);
			}

			item->save();
			delete item;
		}
	}
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

    @param MessageComposer reference
    @return none
*/
void Player::send(const MessageComposer &composer) {
    this->network_connection->send(composer);
}

/*
	Send alert message to session's socket

	@param alert message
	@param url (optional: don't add )
	@return none
*/
void Player::sendAlert(const std::string alert_message, const std::string url) {
	this->network_connection->send(BroadcastMessageAlertComposer(alert_message, url));
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

	if (network_connection == nullptr) {
		return;
	}

    this->getNetworkConnection()->setConnectionState(false);

    if (Icarus::getLogConfiguration()->getBool("log.player.disconnect")) {
        cout << " [SESSION] Client disconnected with ID: " << this->getNetworkConnection()->getConnectionId() << endl;
    }

    if (this->logged_in) {
        messenger->sendStatus(true); // offline for everyone :'(
    }

    delete messenger;
	delete messenger_user;
	delete inventory;
    delete session_details;
    delete room_user;
}
