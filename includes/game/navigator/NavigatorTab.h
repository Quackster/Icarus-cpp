#pragma once
#include <string>

using namespace std;

class NavigatorTab
{
public:
    NavigatorTab(int id, int child_id, string tab_name, string title, char button_type, bool closed, bool thumbnail);
    ~NavigatorTab();

    vector<NavigatorTab*> getChildTabs();

    int getId() { return id; }
    int getChildId() { return child_id; }
    string getTabName() { return tab_name; }
    string getTitle() { return title; }
    char getButtonType() { return button_type; }
    bool getClosed() { return closed; }
    bool getThumbnail() { return thumbnail; }

private:
    int id;
    int child_id;
    string tab_name;
    string title;
    char button_type;
    bool closed;
    bool thumbnail;
};

