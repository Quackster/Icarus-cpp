#include "stdafx.h"
#include "game/navigator/NavigatorTab.h"


NavigatorTab::NavigatorTab(int id, int child_id, string tab_name, string title, char button_type, bool closed, bool thumbnail) :
    id(id), child_id(child_id), tab_name(tab_name), title(title), button_type(button_type), closed(closed), thumbnail(thumbnail)
{
}


NavigatorTab::~NavigatorTab()
{
}
