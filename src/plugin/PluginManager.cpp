#include "stdafx.h"

#include "boot/Icarus.h"

#include "PluginManager.h"
#include "PluginMessageEvent.h"

#include "lua.hpp"

#include <boost/filesystem.hpp> 

PluginManager::PluginManager() {

	std::string directory = "plugins";

   boost::filesystem::path dir(directory);

   if (!boost::filesystem::exists(directory)) {
	   if (!boost::filesystem::create_directory(dir)) {
		   cout << "FAILED: Could not create " << directory << " directory!" << endl;
	   }
   }
}


PluginManager::~PluginManager() {
}

void PluginManager::loadPlugins() {

	lua_State *L = luaL_newstate();



}
