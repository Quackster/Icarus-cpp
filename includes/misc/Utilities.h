#pragma once
#include <vector>
#include <string>

class Utilities
{

private:
    Utilities() { };

public:
    static std::vector<std::string> split(const std::string &s, char delim);

};

