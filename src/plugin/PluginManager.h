#pragma once
#include <iostream>
#include <ctime>

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/dispatchkit/bootstrap_stl.hpp>
#include <chaiscript/dispatchkit/function_call.hpp>

class PluginMessageEvent;
class PluginManager
{
public:
	PluginManager();
	~PluginManager();
	void loadPlugins();

	void print(const std::string &msg) {
		std::cout << "[" << time(nullptr) << "] " << msg << '\n';
	}

	void log(const std::string &module, const std::string &msg) {
		std::cout << "[" << time(nullptr) << "] <" << module << "> " << msg << '\n';
	}

	std::map<std::string, std::function<void (const PluginMessageEvent&)> > m_callbacks;

	void add_callback(const std::string &t_name, const std::function<void(const PluginMessageEvent&)> &t_func);
	void do_callbacks(const std::string &inp);

private:

};

