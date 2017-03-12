#include "stdafx.h"

#include "plugin/Plugin.h"

#include "plugin/events/EventFactory.h"
#include "communication/incoming/MessageHandler.h"

#include "lua.hpp"


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

	EventFactory::addObjects(this);
	MessageHandler::addObjects(this);
}

/*template <class T>
T Plugin::testEvent() {

	for (std::string event_name : this->events) {
		if (event_name == "LoginEvent") {

			Event *event = std::make_shared<PlayerLoginEvent>().get();// new PlayerLoginEvent();

			luabridge::LuaRef enable_callback = luabridge::getGlobal(this->L, "onLoginEvent");
			Event *pevent = enable_callback(event);
			std::
			<< pevent->isCancelled() << std::endl;

			delete pevent;

		}
	}
}*/

Plugin::~Plugin() {
	lua_close(this->L);
}