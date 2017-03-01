#pragma once

#include <vector>

class lua_State;

class Plugin {

public:
	Plugin(std::string path, std::string name, std::string author);
	~Plugin();

	void setup();

	std::string &getPath() { return this->path; }
	std::string &getName() { return this->name; }
	std::string &getAuthor() { return this->author; }
	std::vector<std::string> &getEvents() { return this->events; }
	lua_State *getLuaState() { return L; }
private:
	std::string path;
	std::string name;
	std::string author;
	std::vector<std::string> events;
	lua_State *L;
};

