#include "stdafx.h"

#include "plugin/Plugin.h"

#include "plugin/events/Event.h"
#include "plugin/events/EventFactory.h"
#include "plugin/events/player/PlayerLoginEvent.h"

#include "lua.hpp"
#include "LuaBridge.h"

#include "game/player/Player.h"
#include "game/entities/Entity.h"


EventFactory::EventFactory() {

}

EventFactory::~EventFactory() {

}

void EventFactory::addObjects(Plugin *plugin) {

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <Plugin>("Plugin")
		.addFunction("getName", &Plugin::getName)
		.addFunction("getAuthor", &Plugin::getAuthor)
		.endClass();

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <Entity>("Entity")
		.addFunction("getDetails", &Entity::getDetails)
		.endClass()
		.deriveClass <Player, Entity>("Entity")
		.addFunction("sendAlert", &Player::sendAlert)
		.endClass();

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <EntityDetails>("EntityDetails")
		.addData("username", &EntityDetails::username)
		.addData("id", &EntityDetails::id)
		.addData("credits", &EntityDetails::credits)
		.addData("motto", &EntityDetails::motto)
		.addData("rank", &EntityDetails::rank)
		.addData("authenticated", &EntityDetails::authenticated)
		.endClass();

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <Event>("Event")
		.addFunction("isCancelled", &Event::isCancelled)
		.addFunction("setCancelled", &Event::setCancelled)
		.endClass()
		.deriveClass <PlayerLoginEvent, Event>("PlayerLoginEvent")
		.addFunction("getPlayer", &PlayerLoginEvent::getPlayer)
		.addFunction("getTicket", &PlayerLoginEvent::getTicket)
		.addFunction("getTestingClass", &PlayerLoginEvent::getTestingClass)
		.endClass();
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