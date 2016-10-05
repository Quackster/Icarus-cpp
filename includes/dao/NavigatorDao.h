#pragma once
#include <vector>
#include <string>

#include "game/navigator/NavigatorTab.h"
#include "game/navigator/NavigatorCategory.h"

#include "mysql_connection.h"
#include "mysql.h"

using namespace std;

class NavigatorDao
{

private:
    NavigatorDao() { };

public:
    static vector<NavigatorTab*> *getTabsByChildId(int child_id);
    static vector<NavigatorCategory*> *getCategories();

};

