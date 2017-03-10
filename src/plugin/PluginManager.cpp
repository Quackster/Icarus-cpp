#include "stdafx.h"

#include "boot/Icarus.h"
#include "misc/Utilities.h"

#include "Plugin.h"
#include "PluginManager.h"
#include "plugin/events/Event.h"
#include "plugin/events/EventFactory.h"

#include "lua.hpp"
#include "LuaBridge.h"

#include <boost/filesystem.hpp> 

#include "plugin/events/player/PlayerLoginEvent.h"

#include <fstream>

PluginManager::PluginManager() {

	this->plugins = new std::vector<Plugin*>();
	this->plugin_paths = new std::vector<std::string>();
	this->registered_events = new std::map<std::string, std::vector<Plugin*>>();

	std::string directory = "plugins";

	boost::filesystem::path dir(directory);

	if (!boost::filesystem::exists(directory)) {
		if (!boost::filesystem::create_directory(dir)) {
			cout << "FAILED: Could not create " << directory << " directory!" << endl;
		}
	}

	cout << endl;
	cout << " [BOOT] [PluginManager] Loading plugin system..." << endl;
	cout << endl;
}

PluginManager::~PluginManager() {
}

/*
	Reads all files to load as plugins from 
	plugins/plugin_register.lua which then interprets it as Lua and
	saves the plugin paths into a vector

	@return none
*/
void PluginManager::loadPlugins() {

	std::string plugin_register = "plugins/plugin_register.lua";

	if (!std::ifstream(plugin_register)) {
		std::ofstream output_file;
		output_file.open(plugin_register);

		output_file << "plugins = {" << endl;
		output_file << "    ";
		output_file << "}";

		output_file.close();
	}

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_dofile(L, plugin_register.c_str()) != LUA_OK) {
		return;
	}
	
	luabridge::LuaRef plugins_ref = luabridge::getGlobal(L, "plugins");
	
	for (int i = 1; i < plugins_ref.length() + 1; i++) {
		plugin_paths->push_back(plugins_ref[i].cast<std::string>());
	}

	for (std::string plugin_path : *this->plugin_paths) {
		this->getPluginDetails(plugin_path);
	}
	
	lua_close(L);
}

/*
	Gets all plugin details for each plugin, which is the name, author
	and what events it's registered

	@param Lua file path
	@return none
*/
void PluginManager::getPluginDetails(std::string path) {

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_dofile(L, path.c_str()) != LUA_OK) {
		return;
	}

	luabridge::LuaRef plugins_ref = luabridge::getGlobal(L, "plugin_details");
	luabridge::LuaRef plugin_events = luabridge::getGlobal(L, "events");

	Plugin *plugin = new Plugin(
		path,
		plugins_ref["name"].cast<std::string>(),
		plugins_ref["author"].cast<std::string>());

	std::vector<std::string> events;

	for (int i = 1; i < plugin_events.length() + 1; i++) {

		std::string event = plugin_events[i].cast<std::string>();
		events.push_back(event);
	}

	for (auto event : events) {

		/*
		Create a look up table to see what plugins are registered to watch event.

		If the event entry doesn't exist, we'll add it along with the plugin instance for that event.
		If the event entry already exists, we'll just add the plugin instance associated with that event
		*/

		// pfefijewfew

		/*
			dwdqdwqdwqd
		*/

		plugin->getEvents().push_back(event);

		if (this->registered_events->count(event) > 0) {
			std::vector<Plugin*> &plugin_list = this->registered_events->find(event)->second;
			plugin_list.push_back(plugin);
		}
		else {
			this->registered_events->insert(std::make_pair(event, std::vector<Plugin*>()));
			this->registered_events->find(event)->second.push_back(plugin);

		}
	}

	lua_close(L);

	cout << " [Plugin] Loaded plugin '"
		<< plugin->getName() << "' by "
		<< plugin->getAuthor()
		<< " with (" << plugin->getEvents().size() << ") events" << endl;

	this->plugins->push_back(plugin);
}

/*
	Sets up each plugin so they can be invoked with events, and 
	gives each plugin access to classes throughout the source-code

	@param none
	@return none
*/
void PluginManager::enablePlugins() {

	for (Plugin *plugin : *this->plugins) {
		plugin->setup();
		luabridge::LuaRef enable_method = luabridge::getGlobal(plugin->getLuaState(), "onEnable");
		enable_method(plugin);
	}
}

/*
	Calls the events and invokes the registered plugins

	@param smart ptr Event
	@return modified Event
*/
Event* PluginManager::callEvent(std::shared_ptr<Event> event) {

	std::string event_name = event->getEventName();
	std::string class_name = event->getClassName();

	for (auto kvp : *this->registered_events) {
		if (kvp.first != class_name) {
			continue;
		}

		for (Plugin *plugin : kvp.second) {

			luabridge::LuaRef ref = luabridge::getGlobal(plugin->getLuaState(), event->getEventName().c_str());
			Event *retrived = EventFactory::cast(event, ref);
			return retrived;

		}
	}

	return event.get();
}