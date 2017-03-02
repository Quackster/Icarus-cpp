#include "stdafx.h"

#include "plugin/Plugin.h"

#include "plugin/events/Event.h"
#include "plugin/events/EventFactory.h"
#include "plugin/events/player/PlayerLoginEvent.h"

#include "lua.hpp"
#include "LuaBridge.h"

EventFactory::EventFactory() {

}

EventFactory::~EventFactory() {

}

/*
	Casts the Event to the correct derived class to that the event handler
	can do finer adjustmenets and receive the correct event information

	@param smart ptr Event
	@param luabridge event handler reference
	@return modified Event
*/
Event *EventFactory::cast(std::shared_ptr<Event> event, luabridge::LuaRef ref) {

	if (event->getClassName() == "PlayerLoginEvent") {
		return ref(dynamic_cast<PlayerLoginEvent*>(event.get()));
	}

	return event.get();
}