#include "stdafx.h"

#include "plugin/Plugin.h"

#include "lua.hpp"
#include "LuaBridge.h"

#include "plugin/events/Event.h"
#include "plugin/events/player/PlayerLoginEvent.h"

#include "game/player/Player.h"
#include "game/entities/Entity.h"

using namespace luabridge;

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

	getGlobalNamespace(L)
		.beginClass <Entity>("Entity")
		.addFunction("getDetails", &Entity::getDetails)
		.endClass()
		.deriveClass <Player, Entity>("Entity")
		.endClass();

	getGlobalNamespace(L)
		.beginClass <Event>("Event")
		.addFunction("isCancelled", &Event::isCancelled)
		.addFunction("setCancelled", &Event::setCancelled)
		.endClass()
		.deriveClass <PlayerLoginEvent, Event>("Event")
		.addFunction("getPlayer", &PlayerLoginEvent::getPlayer)
		.addFunction("getTicket", &PlayerLoginEvent::getTicket)
		.endClass();
}

Plugin::~Plugin() {
	lua_close(this->L);
}