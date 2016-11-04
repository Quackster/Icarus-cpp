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
#include <cctype>
#include <functional>
#include <numeric>

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

/*
    Escape strings from nasty input

    @param string to escape
    @param bool allow breaks
    @param remove everything except letters and numbers
    @return escaped string
*/
std::string Utilities::escape(std::string &str, bool allow_breaks, bool strip_non_alphanumeric) {

    if (str.length() > 0) {

        str = replaceChar(str, (char)1, ' ');
        str = replaceChar(str, (char)2, ' ');
        str = replaceChar(str, (char)3, ' ');
        str = replaceChar(str, (char)9, ' ');

        if (!allow_breaks)
        {
            str = replaceChar(str, (char)10, ' ');
            str = replaceChar(str, (char)13, ' ');
        }

        if (strip_non_alphanumeric) {
            str = escapeEverything(str);
        }
    }

    return str;
}

/*
    Escape input everything and remove eveyrthing that isn't a letter

    @param string to escape
    @return fixed string
*/
std::string Utilities::escapeEverything(std::string &s) {


    for (std::string::iterator i = s.begin(); i != s.end(); i++)
    {
        char ch = s.at(i - s.begin());

        if (!isalpha(ch))
        {
            s.erase(i);
            i--;
        }
    }

    return s;
}

/*
    Replace char in string

    @param string to edit
    @param find char to replace
    @param replace with
    @return fixed string
*/
std::string Utilities::replaceChar(std::string &str, char ch1, char ch2) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ch1)
            str[i] = ch2;
    }

    return str;
}

/*
    Joins string of vectors with delimeter

    @param vector of strings
    @param delimeter
    @return concatinated string
*/
std::string Utilities::join(std::vector<std::string> strings, std::string delim) {

    if (strings.size() > 0) {

        return std::accumulate(std::next(strings.begin()), strings.end(), strings[0], [](std::string a, std::string b) {
            return a + ',' + b;
        });
    }
    else {
        return "";
    }
}