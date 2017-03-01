#include "stdafx.h"

#include "boot/Icarus.h"
#include "misc/Utilities.h"

#include "PluginManager.h"
#include "PluginMessageEvent.h"

#include "lua.hpp"
#include "LuaBridge.h"

#include <boost/filesystem.hpp> 

using namespace luabridge;

PluginManager::PluginManager() {

	std::string directory = "plugins";

	boost::filesystem::path dir(directory);

	if (!boost::filesystem::exists(directory)) {
		if (!boost::filesystem::create_directory(dir)) {
			cout << "FAILED: Could not create " << directory << " directory!" << endl;
		}
	}

	std::cout << std::endl;
	std::cout << " [BOOT] [PluginManager] Loading plugin system..." << std::endl;
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
		plugin_paths.push_back(plugins_ref[i].cast<std::string>());
	}

	for (std::string plugin_path : this->plugin_paths) {
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

	LuaRef plugins_ref = getGlobal(L, "plugin_details");

	std::string plugin_name = plugins_ref["name"].cast<std::string>();
	std::string plugin_author = plugins_ref["author"].cast<std::string>();

	std::vector<std::string> events_registered;

	LuaRef plugin_events = getGlobal(L, "events");

	for (int i = 1; i < plugin_events.length() + 1; i++) {
		events_registered.push_back(plugin_events[i].cast<std::string>());
	}

	std::cout << " [Plugin] Loading plugin '" 
		<< plugin_name << "' by " 
		<< plugin_author 
		<< " with events ['" 
		<< Utilities::join(events_registered, "', '")
		<< "']" << endl;

	lua_close(L);

}
