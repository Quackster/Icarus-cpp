#include "stdafx.h"
#include "game/navigator/NavigatorCategory.h"


NavigatorCategory::NavigatorCategory(int id, std::string name, int minimum_rank) :
    id(id), 
    name(name), 
    minimum_rank(minimum_rank) { }

NavigatorCategory::~NavigatorCategory() { }
