#include "stdafx.h"

#include "plugin/Plugin.h"

#include "lua.hpp"
#include "LuaBridge.h"

#include "plugin/events/Event.h"
#include "plugin/events/player/PlayerLoginEvent.h"

#include "game/player/Player.h"
#include "game/entities/Entity.h"


Plugin::Plugin(std::string path, std::string name, std::string author) :
	path(path),
	name(name),
	author(author),
	events(events) { 
}

void Plugin::setup() {

	this->L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_dofile(L, this->path.c_str()) != LUA_OK) {
		return;
	}

	luabridge::getGlobalNamespace(L)
		.beginClass <Entity>("Entity")
		.addFunction("getDetails", &Entity::getDetails)
		.endClass()
		.deriveClass <Player, Entity>("Entity")
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass <EntityDetails>("EntityDetails")
		.addData("username", &EntityDetails::username)
		.addData("id", &EntityDetails::id)
		.addData("credits", &EntityDetails::credits)
		.addData("motto", &EntityDetails::motto)
		.addData("rank", &EntityDetails::rank)
		.addData("authenticated", &EntityDetails::authenticated)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass <Event>("Event")
		.addFunction("isCancelled", &Event::isCancelled)
		.addFunction("setCancelled", &Event::setCancelled)
		.endClass()
		.deriveClass <PlayerLoginEvent, Event>("PlayerLoginEvent")
		.addFunction("getPlayer", &PlayerLoginEvent::getPlayer)
		.addFunction("getTicket", &PlayerLoginEvent::getTicket)
		.addFunction("getTestingClass", &PlayerLoginEvent::getTestingClass)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass <TestingClass>("TestingClass")
		.addFunction("getTest", &TestingClass::getTest)
		.endClass();
}

/*template <class T>
T Plugin::testEvent() {

	for (std::string event_name : this->events) {
		if (event_name == "LoginEvent") {

			Event *event = std::make_shared<PlayerLoginEvent>().get();// new PlayerLoginEvent();

			luabridge::LuaRef enable_callback = luabridge::getGlobal(this->L, "onLoginEvent");
			Event *pevent = enable_callback(event);
			std::cout << pevent->isCancelled() << std::endl;

			delete pevent;

		}
	}
}*/

Plugin::~Plugin() {
	lua_close(this->L);
}