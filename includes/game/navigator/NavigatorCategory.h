#pragma once
#include <string>

using namespace std;

class NavigatorCategory
{
public:
    NavigatorCategory(int id, string name, int min_rank);
    ~NavigatorCategory();
    int getId() { return id; }
    string getName() { return name; }
    int getMinimumRank() { return minimumRank;  }

private:
    int id;
    string name;
    int minimumRank;

};

