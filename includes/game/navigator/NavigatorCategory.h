#pragma once
#include <string>

class NavigatorCategory
{
public:
    NavigatorCategory(int id, std::string name, int min_rank);
    ~NavigatorCategory();
    int getId() { return id; }
    std::string getName() { return name; }
    int getMinimumRank() { return minimumRank;  }

private:
    int id;
    std::string name;
    int minimumRank;

};

