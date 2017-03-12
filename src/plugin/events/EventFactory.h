#pragma once
#include <memory>

#include "lua.hpp"
#include "LuaBridge.h"

class Event;
class Plugin;
class EventFactory {

public:
	EventFactory();
	~EventFactory();

	static void addObjects(Plugin *plugin);
	static Event *cast(std::shared_ptr<Event> event, luabridge::LuaRef ref);

};