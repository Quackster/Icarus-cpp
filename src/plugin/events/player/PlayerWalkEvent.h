#pragma once
#include <string>


#include "game/player/Player.h"
#include "game/room/Room.h"

#include "plugin/events/Event.h"

class Plugin;
class PlayerWalkEvent : public Event {

public:
	PlayerWalkEvent(Player *player) :
		player(player) { 
		this->room = this->player->getRoomUser()->getRoom();
	}
	
	~PlayerWalkEvent() { }

	Player *getPlayer() { return player; }
	Room *getRoom() { return room; }

	Position *getPosition() { return &player->getRoomUser()->position; }
	Position *getGoal() { return &player->getRoomUser()->goal; }

	std::string getClassName() {
		return "PlayerMoveEvent";
	}
	
	std::string getEventName() {
		return "onPlayerMoveEvent";
	}

private:
	Player *player;
	Room *room;

};