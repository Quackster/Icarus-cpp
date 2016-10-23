/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include <sstream>
#include <string>
#include <algorithm>
#include <locale> 

#include "Utilities.h"

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

/*
    Trims whitespace from string

    @param string
    @return trimmed string
*/
std::string Utilities::trim(std::string &str) {

    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/*
    Checks if given string is a number

    @param string to check
    @return true if number, false if not
*/
bool Utilities::isNumber(const std::string& s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}