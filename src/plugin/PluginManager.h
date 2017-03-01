#pragma once
#include <iostream>
#include <ctime>



class PluginMessageEvent;
class PluginManager
{
public:
	PluginManager();
	~PluginManager();
	void loadPlugins();
	void getPluginDetails(std::string path);

private:
	std::vector<std::string> plugin_paths;

};

