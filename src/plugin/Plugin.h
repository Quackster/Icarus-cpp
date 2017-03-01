#pragma once

#include <vector>

class lua_State;

struct Plugin {
	std::string name;
	std::string author;
	std::vector<std::string> events;
	lua_State *L;
};

