#pragma once
#include <vector>
#include <string>

#include "game/navigator/NavigatorTab.h"
#include "game/navigator/NavigatorCategory.h"

#include "mysql_connection.h"
#include "mysql.h"

class NavigatorDao
{

private:
    NavigatorDao() { };

public:
    static std::vector<NavigatorTab*> *getTabsByChildId(int child_id);
    static std::vector<NavigatorCategory*> *getCategories();

};

