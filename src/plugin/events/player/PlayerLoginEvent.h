#pragma once
#include <string>

#include "TestingClass.h"
#include "game/player/Player.h"
#include "plugin/events/Event.h"

class Plugin;
class PlayerLoginEvent : public Event {

public:
	PlayerLoginEvent(Player *player, std::string ticket) : 
		player(player),
		ticket(ticket) { }
	
	~PlayerLoginEvent() { }

	Player *getPlayer() { return player; }
	std::string getTicket() { return ticket; }
	TestingClass *getTestingClass() { return testingclass; }

	std::string getClassName() {
		return "PlayerLoginEvent";
	}
	
	std::string getEventName() {
		return "onPlayerLoginEvent";
	}

private:
	Player *player;
	std::string ticket;
	TestingClass *testingclass = new TestingClass();

};