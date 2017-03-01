#include "stdafx.h"

#include "boot/Icarus.h"
#include "misc/Utilities.h"

#include "Plugin.h"
#include "PluginManager.h"
#include "PluginMessageEvent.h"

#include "lua.hpp"
#include "LuaBridge.h"

#include <boost/filesystem.hpp> 

using namespace luabridge;

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

	std::cout << std::endl;
	std::cout << " [BOOT] [PluginManager] Loading plugin system..." << std::endl;
	std::cout << std::endl;
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

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_dofile(L, "plugins/plugin_register.lua") != LUA_OK) {
		return;
	}
	
	LuaRef plugins_ref = getGlobal(L, "plugins");
	
	for (int i = 1; i < plugins_ref.length() + 1; i++) {
		plugin_paths->push_back(plugins_ref[i].cast<std::string>());
	}

	for (std::string plugin_path : *this->plugin_paths) {
		this->getPluginDetails(plugin_path);
	}
	
	lua_close(L);
}

void PluginManager::enablePlugins() {

	for (auto plugin : *this->plugins) {

		plugin->setup();

		LuaRef enable_callback = getGlobal(plugin->getLuaState(), "onEnable");
		enable_callback();
	}
}

/*
	Gets all plugin details for each plugin, which is the name, author
	and what events it's registered

	@param Lua file path
	@return none
*/
void PluginManager::getPluginDetails(std::string path) {

	try {
		lua_State *L = luaL_newstate();
		luaL_openlibs(L);

		if (luaL_dofile(L, path.c_str()) != LUA_OK) {
			return;
		}

		LuaRef plugins_ref = getGlobal(L, "plugin_details");
		LuaRef plugin_events = getGlobal(L, "events");

		std::vector<std::string> events;

		for (int i = 1; i < plugin_events.length() + 1; i++) {

			std::string event = plugin_events[i].cast<std::string>();
			events.push_back(event);
		}

		Plugin *plugin = new Plugin(
			path, 
			plugins_ref["name"].cast<std::string>(), 
			plugins_ref["author"].cast<std::string>());

		for (auto event : events) {

			/*
			Create a look up table to see what plugins are registered to watch event.

			If the event entry doesn't exist, we'll add it along with the plugin instance for that event.
			If the event entry already exists, we'll just add the plugin instance associated with that event
			*/
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

		std::cout << " [Plugin] Loading plugin '"
			<< plugin->getName() << "' by "
			<< plugin->getAuthor()
			<< " with (" << plugin->getEvents().size() << ") events" << endl;

		this->plugins->push_back(plugin);

	}
	catch (std::exception& e) {
		cout << endl << " Error occurred: " << e.what() << endl;
	}
	catch (...) {
		cout << endl << " Error occurred, but we couldn't grab the message" << endl;
	}
}
