#pragma once
#include <string>

#include "plugin/events/Event.h"

class Plugin;
class PlayerTryLoginEvent : public Event {

public:
	PlayerTryLoginEvent(std::string ip_address, std::string ticket) :
		ip_address(ip_address),
		ticket(ticket) { }
	
	~PlayerTryLoginEvent() { }

	std::string getIpAddress() { return ip_address; }
	std::string getTicket() { return ticket; }

	std::string getClassName() {
		return "PlayerTryLoginEvent";
	}
	
	std::string getEventName() {
		return "onTryLoginEvent";
	}

private:
	std::string ip_address;
	std::string ticket;

};