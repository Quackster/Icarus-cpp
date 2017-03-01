#pragma once
#include <string>

#include "plugin/events/Event.h"

class Player;
class Plugin;
class PlayerLoginEvent : public Event {

public:
	PlayerLoginEvent(Player &player, std::string ticket) : 
		player(player),
		ticket(ticket) { }
	
	~PlayerLoginEvent() { }

	Player &getPlayer() { return player; }
	std::string getTicket() { return ticket; }

private:
	Player &player;
	std::string ticket;

};