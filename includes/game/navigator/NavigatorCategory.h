#pragma once
#include <string>

class NavigatorCategory
{
public:
    NavigatorCategory(int id, std::string name, int minimum_rank);
    ~NavigatorCategory();
    int getId() { return id; }
    std::string getName() { return name; }
    int getMinimumRank() { return minimum_rank;  }

private:
    int id;
    std::string name;
    int minimum_rank;

};

