#include "stdafx.h"

#include <sstream>

#include "misc/Utilities.h"



/*
Splits a given string by delimeter

@param string to split
@param delimenter
@return vector which has split up the string
*/
vector<string> Utilities::split(const string &s, char delim) {

    stringstream ss(s);
    string item;
    vector<string> tokens;

    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}