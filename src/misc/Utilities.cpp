#include "stdafx.h"
#include <sstream>
#include "misc/Utilities.h"

/*
Splits a given string by delimeter

@param string to split
@param delimenter
@return vector which has split up the string
*/
std::vector<std::string> Utilities::split(const std::string &s, char delim) {

    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;

    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }

    return tokens;
}