#pragma once
#include <iostream>
#include <ctime>
#include <map>

class Plugin;
class Event;

class PluginManager
{
public:
	PluginManager();
	~PluginManager();
	void loadPlugins();
	void enablePlugins();
	void getPluginDetails(std::string path);
	Event *callEvent(std::shared_ptr<Event> event);

private:
	std::vector<Plugin*> *plugins;
	std::map<std::string, std::vector<Plugin*>> *registered_events;
	std::vector<std::string> *plugin_paths;

};

