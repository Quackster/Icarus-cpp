#pragma once
#include <string>

using namespace std;

class NavigatorTab
{
public:
    NavigatorTab(int id, int childId, string tabName, string title, char button_type, bool closed, bool thumbnail);
    ~NavigatorTab();

    vector<NavigatorTab*> getChildTabs();

    int getId() { return id; }
    int getChildId() { return childId; }
    string getTabName() { return tabName; }
    string getTitle() { return title; }
    char getButtonType() { return buttonType; }
    bool getClosed() { return closed; }
    bool getThumbnail() { return thumbnail; }

private:
    int id;
    int childId;
    string tabName;
    string title;
    char buttonType;
    bool closed;
    bool thumbnail;
};

