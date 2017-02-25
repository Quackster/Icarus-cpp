#include "stdafx.h"

#include "boot/Icarus.h"

#include "PluginManager.h"
#include "PluginMessageEvent.h"


PluginManager::PluginManager()
{
}


PluginManager::~PluginManager()
{
}

void PluginManager::add_callback(const std::string &t_name, const std::function<void(const PluginMessageEvent&)> &t_func)
{
	std::cout << "testing" << endl;
	m_callbacks[t_name] = t_func;
}


void PluginManager::do_callbacks(const std::string &inp)
{
	print("Running Callbacks: " + inp);

	for (std::map<std::string, std::function<void(const PluginMessageEvent&)>>::iterator itr = m_callbacks.begin();

		itr != m_callbacks.end();

		++itr)
	{
		const PluginMessageEvent event = PluginMessageEvent(new Player(nullptr), Request(0, nullptr));
		itr->second(event);
	}
}

void PluginManager::loadPlugins() {

	using namespace chaiscript;

	ChaiScript chai;

	PluginManager plugin_manager = Icarus::getGame()->getPluginManager();

	chai.add_global(var(&plugin_manager), "plugin_manager");

	chai.add(fun(&PluginManager::add_callback, std::ref(plugin_manager)), "add_callback_bound");
	chai.add(fun(&PluginManager::add_callback), "add_callback");
	chai.add(fun(&PluginManager::do_callbacks), "do_callbacks");
	chai.add(fun(&PluginManager::print), "log_info");

	chai.add(fun(&PluginMessageEvent::player), "player");
	chai.add(fun(&PluginMessageEvent::player), "player");
	chai.add(user_type<PluginMessageEvent>(), "PluginMessageEvent");


	chai.eval_file("testing.chai");
	//chai.eval("plugin_manager.add_callback(\"test\", fun(PluginMessageEvent o) {  });");

	std::cout << "Callbacks: " << m_callbacks.size() << endl;
}
