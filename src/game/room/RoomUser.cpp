/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "Room.h"

#include "boot/Icarus.h"


#include "game/item/Item.h"
#include "game/entities/Entity.h"

#include "communication/outgoing/room/user/UserStatusMessageComposer.h"
#include "communication/outgoing/room/user/TalkMessageComposer.h"
#include "communication/outgoing/room/user/FloodFilterMessageComposer.h"
#include "communication/outgoing/room/user/IdleStatusMessageComposer.h"

/*
    Constructor for room user
*/
RoomUser::RoomUser(Entity *entity) : entity(entity) { 
    this->reset();
}

/*
    Updatest status, if value is empty, the status entry will be deleted

    @param status key
    @param status value
    @return none
*/
void RoomUser::setStatus(std::string key, std::string value, bool force_update) {

    if (value.length() > 0) {
        this->statuses[key] = value;
    }
    else {
        this->statuses.erase(key);
    }

    if (force_update) {
        this->updateStatus();
        //this->needs_update = true;
		//this->room->send(UserStatusMessageComposer(this->entity));
    }
}

/*
    Returns true or not if the user currently has a status

    @param status key
    @return boolean
*/
bool RoomUser::containsStatus(std::string key) {
    return this->statuses.count(key) > 0;
}

/*
    Schedule player status to be updated for everyone in a room, loop happens every 0.5s
    this technically doesn't run instantly

    @return none
*/
void RoomUser::updateStatus() {
    this->needs_update = true;
}
/*
    Sets rotation of user, optional to set head rotation too, and also optional to update player status

    @param body rotation
    @param head rotation
    @param bool update
    @return none
*/
void RoomUser::setRotation(int rotation, bool set_head_rotation, bool update) {
    this->rotation = rotation;
    
    if (set_head_rotation) {
        this->head_rotation = rotation;
    }
}

/*
    Restores all room user values (used when a user leaves the room)

    @return none
*/
void RoomUser::reset() {
    this->last_chat_id = 0;
    this->dance_id = 0;
    this->position = Position();
    this->goal = Position();
    this->rotation = 0;
    this->head_rotation = 0;
    this->statuses.clear();// = std::map<std::string, std::string>();
    this->path.clear();// = std::queue<Position>();
    this->room = nullptr;
	this->current_item = nullptr;
    this->in_room = false;
    this->is_walking = false;
    this->is_loading_room = false;
    this->next = Position();
    this->chat_count = 0;
    this->chat_flood_timer = 0;
    this->sign_time = 0;
    this->afk_time = 0;
    this->is_asleep = false;

}

/*
    Walking handler

    @return none
*/
void RoomUser::walk() {

    if (this->is_walking) {
        if (!this->next.isEmpty()) {

            Position next = this->next;
            int height = this->getRoom()->getModel()->getSquareHeight(next.x, next.y);

            this->position = next;
            this->height = height;
        }
        else {
            this->setStatus("mv", "");
            this->is_walking = false;
			this->stopWalking();
        }
    }
}

/*
    Stop walking handler, called when a user stops walking

    @return none
*/
void RoomUser::stopWalking() {

	Room *room = this->room;
	RoomModel *model = this->room->getModel();

	if (this->position.x == model->door_x &&
		this->position.y == model->door_y) {

		this->leaveRoom();
		return;
	}

	Item *item = this->room->getDynamicModel()->getItemAtPosition(this->position.x, this->position.y);

	if (item != nullptr) {
		if (item->getDefinition()->can_sit || item->getDefinition()->interaction_type == "bed") {

			this->current_item = item;
			this->currentItemTrigger();
		}
	}
}

void RoomUser::currentItemTrigger() {
	
	if (this->current_item == nullptr) {
		this->setStatus("sit", "");
		this->setStatus("lay", "");
	}
	else {

		Item *item = this->current_item;

		int item_height = item->z + item->getDefinition()->stack_height;
		this->setRotation(item->rotation, true, false);

		if (item->getDefinition()->can_sit) {
			this->setStatus("sit", std::to_string(item_height + 0.04));
		}
		else {
			this->setStatus("lay", std::to_string(item_height + 0.65));
		}
	}

	this->updateStatus();
}

/*
    Chat handler

    @param message to chat
    @param chat bubble type
    @param count
    @param shout (default is false)
    @param spam check (default is true)
    @return none
*/
void RoomUser::chat(std::string message, int bubble, int count, bool shout, bool spam_check) {

    int MAX_CHAT_BEFORE_FLOOD = Icarus::getGameConfiguration()->getInt("chat.flood.max");
    int CHAT_FLOOD_SECONDS = Icarus::getGameConfiguration()->getInt("chat.flood.seconds");
    int CHAT_FLOOD_WAIT = Icarus::getGameConfiguration()->getInt("chat.flood.wait");

    bool is_staff = false;
    Player *player = nullptr;

    if (dynamic_cast<Player*>(this->entity) != NULL) {

        player = dynamic_cast<Player*>(this->entity);
        is_staff = player->hasFuse("moderator");
    }

    // if current time less than the chat flood timer (last chat time + seconds to check)
    // say that they still need to wait before shouting again
    if (spam_check) {
        if (Icarus::getUnixTimestamp() < this->chat_flood_timer && this->chat_count >= MAX_CHAT_BEFORE_FLOOD) {

            if (!is_staff) {
                if (player != nullptr) {
                    player->send(FloodFilterMessageComposer(CHAT_FLOOD_WAIT));
                }
                return;
            }
        }
    }

    // TODO: Check if not bot
    // The below function validates the chat bubbles

    if (entity->getEntityType() == PLAYER) {
        if (bubble == 2 || (bubble == 23 && !player->hasFuse("moderator")) || bubble < 0 || bubble > 29 || bubble == 1) {
            bubble = 0;// 0;// this.lastChatId;
        }
    }

    if (entity->getEntityType() == BOT) {
        bubble = 2;
    }

    this->room->send(TalkMessageComposer(this->virtual_id, shout, message, count, bubble));

    // if the users timestamp has passed the check but the chat count is still high
    // the chat count is reset then

    if (spam_check) {
        if (!player->hasFuse("moderator")) {

            if (Icarus::getUnixTimestamp() > this->chat_flood_timer && this->chat_count >= MAX_CHAT_BEFORE_FLOOD) {
                this->chat_count = 0;
            }
            else {
                this->chat_count = this->chat_count + 1;
            }

            this->chat_flood_timer = (Icarus::getUnixTimestamp() + CHAT_FLOOD_SECONDS);

        }
    }
}

/*
    Unidle handler called when user does actions inside the room

    @return none
*/
void RoomUser::awake() {

    this->afk_time = 0;

    if (!this->is_asleep) {
        return;
    }

    this->room->send(IdleStatusMessageComposer(this->virtual_id, false)); 
    this->is_asleep = false;
}

/*
    Leave room handler instead of calling the direct Room->leaveRoom method

    @param go to hotel view after leave room
    @return none
*/
void RoomUser::leaveRoom(bool hotel_view) {

	/*LEAVE ROOM ALERT!
 [ROOM] Room ID 18 unloaded
 [ROOM] Room ID 18 loaded
 [SESSION] [CONNECTION: 2] 1787/ [6]√[0][10]Navigation[0][0][0][11]go.official[0][2]18[0][0][0][0]
 [SESSION] [CONNECTION: 2] 2258/ [8]╥[0][0][0][0][0]    
LEAVE ROOM ALERT!
 [ROOM] Room ID 18 unloaded
 [ROOM] Room ID 18 loaded*/

    if (this->room != nullptr) {
        this->room->leave(this->entity, hotel_view);
    }

}

/*
    Deconstructor for room user
*/
RoomUser::~RoomUser() { }
