#include "stdafx.h"

#include "boot/Icarus.h"

#include "PluginManager.h"


PluginManager::PluginManager()
{
}


PluginManager::~PluginManager()
{
}

void PluginManager::loadPlugins() {

	using namespace chaiscript;

	ChaiScript chai;
	PluginManager manager = Icarus::getGame()->getPluginManager();

	//Create a new system object and share it with the chaiscript engine
	chai.add_global(var(&manager), "system");

	//Add a bound callback method
	chai.add(fun(&PluginManager::add_callback, std::ref(manager)), "add_callback_bound");

	//Register the two methods of the System structure.
	chai.add(fun(&PluginManager::add_callback), "add_callback");
	chai.add(fun(&PluginManager::do_callbacks), "do_callbacks");

	chai.eval("system.add_callback(\"#1\", fun(x) { \"Callback1 \" + x });");

	// Because we are sharing the "system" object with the chaiscript engine we have equal
	// access to it both from within chaiscript and from C++ code
	chai.eval("system.do_callbacks(\"TestString\");");
}
