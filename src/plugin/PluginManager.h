#pragma once
#include <iostream>
#include <ctime>


#include <chaiscript/chaiscript.hpp>
#include <chaiscript/dispatchkit/bootstrap_stl.hpp>
#include <chaiscript/dispatchkit/function_call.hpp>

class PluginManager
{
public:
	PluginManager();
	~PluginManager();
	void loadPlugins();

	void log(const std::string &msg)
	{
		std::cout << "[" << time(nullptr) << "] " << msg << '\n';
	}

	void log(const std::string &module, const std::string &msg)
	{
		std::cout << "[" << time(nullptr) << "] <" << module << "> " << msg << '\n';
	}

	std::map<std::string, std::function<std::string(const std::string &)>> m_callbacks;

	void add_callback(const std::string &t_name, const std::function<std::string(const std::string &)> &t_func) {
		m_callbacks[t_name] = t_func;
	}


	void do_callbacks(const std::string &inp)
	{
		log("Running Callbacks: " + inp);
		for (std::map<std::string, std::function<std::string(const std::string &)>>::iterator itr = m_callbacks.begin();
			itr != m_callbacks.end();
			++itr)
		{
			log("Callback: " + itr->first, itr->second(inp));
		}
	}

private:

};

