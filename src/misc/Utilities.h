/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>
#include <string>

class Utilities
{

private:
    Utilities() { };

public:
    static std::vector<std::string> split(const std::string &s, char delim);
    static std::string trim(std::string &str);
    static bool isNumber(const std::string& s);
    static std::string escape(std::string input, bool allow_breaks = false, bool strip_non_alphanumeric = false, bool replace_spaces = false);
    static std::string removeNonAlphanumeric(std::string &input);
    static std::string replaceChar(std::string &str, char ch1, char ch2);
    static std::string removeChar(std::string &s, char ch1);
    static std::string join(std::vector<std::string> strings, std::string delim);
};

