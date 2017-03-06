#include "stdafx.h"

#include "plugin/Plugin.h"

#include "plugin/events/Event.h"
#include "plugin/events/EventFactory.h"

#include "plugin/events/player/PlayerLoginEvent.h"
#include "plugin/events/player/PlayerTryLoginEvent.h"
#include "plugin/events/player/PlayerWalkEvent.h"

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
		.beginClass <Room>("Room")
		.addFunction("getData", &Room::getData)
		.endClass();

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <RoomData>("RoomData")
		.addData("id", &RoomData::id)
		.addData("name", &RoomData::name)
		.endClass();

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <RoomUser>("RoomUser")
		.addFunction("getRoom", &RoomUser::getRoom)
		.addFunction("chat", &RoomUser::chat)
		.addFunction("setStatus", &RoomUser::setStatus)
		.addFunction("awake", &RoomUser::awake)
		.addFunction("leaveRoom", &RoomUser::leaveRoom)
		.addFunction("setRotation", &RoomUser::setRotation)
		.addFunction("stopWalking", &RoomUser::stopWalking)
		.addFunction("updateStatus", &RoomUser::updateStatus)
		.addData("position", &RoomUser::position)
		.addData("goal", &RoomUser::goal)
		.addData("afk_time", &RoomUser::afk_time)
		.addData("chat_count", &RoomUser::chat_count)
		.addData("chat_flood_timer", &RoomUser::chat_flood_timer)
		.addData("dance_id", &RoomUser::dance_id)
		.addData("is_asleep", &RoomUser::is_asleep)
		.addData("is_walking", &RoomUser::is_walking)
		.addData("head_rotation", &RoomUser::head_rotation)
		.addData("rotation", &RoomUser::rotation)
		.endClass();

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <Position>("Position")
		.addData("x", &Position::x)
		.addData("y", &Position::y)
		.endClass();

	luabridge::getGlobalNamespace(plugin->getLuaState())
		.beginClass <Entity>("Entity")
		.addFunction("getDetails", &Entity::getDetails)
		.endClass()
		.deriveClass <Player, Entity>("Entity")
		.addFunction("sendAlert", &Player::sendAlert)
		.addFunction("getRoomUser", &Player::getRoomUser)
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
		.deriveClass <PlayerTryLoginEvent, Event>("PlayerTryLoginEvent")
		.addFunction("getIpAddress", &PlayerTryLoginEvent::getIpAddress)
		.addFunction("getTicket", &PlayerTryLoginEvent::getTicket)
		.endClass()
		.deriveClass <PlayerLoginEvent, Event>("PlayerLoginEvent")
		.addFunction("getPlayer", &PlayerLoginEvent::getPlayer)
		.addFunction("getTicket", &PlayerLoginEvent::getTicket)
		.endClass()
		.deriveClass <PlayerWalkEvent, Event>("PlayerWalkEvent")
		.addFunction("getPlayer", &PlayerWalkEvent::getPlayer)
		.addFunction("getRoom", &PlayerWalkEvent::getRoom)
		.addFunction("getGoal", &PlayerWalkEvent::getPosition)
		.addFunction("getPosition", &PlayerWalkEvent::getGoal)
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

	if (event->getClassName() == "PlayerTryLoginEvent") {
		return ref(dynamic_cast<PlayerTryLoginEvent*>(event.get()));
	}

	if (event->getClassName() == "PlayerWalkEvent") {
		return ref(dynamic_cast<PlayerWalkEvent*>(event.get()));
	}

	return event.get();
}