#pragma once
#include <vector>
#include <string>

using namespace std;

class Utilities
{

private:
    Utilities() { };

public:
    static vector<string> split(const string &s, char delim);

};

