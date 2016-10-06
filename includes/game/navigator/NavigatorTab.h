#pragma once
#include <string>

class NavigatorTab
{
public:
    NavigatorTab(int id, int childId, std::string tabName, std::string title, char button_type, bool closed, bool thumbnail);
    ~NavigatorTab();

    std::vector<NavigatorTab*> getChildTabs();

    int getId() { return id; }
    int getChildId() { return childId; }
    std::string getTabName() { return tabName; }
    std::string getTitle() { return title; }
    char getButtonType() { return buttonType; }
    bool getClosed() { return closed; }
    bool getThumbnail() { return thumbnail; }

private:
    int id;
    int childId;
    std::string tabName;
    std::string title;
    char buttonType;
    bool closed;
    bool thumbnail;
};

