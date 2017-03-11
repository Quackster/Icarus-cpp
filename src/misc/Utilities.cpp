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
#include <fstream>

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>


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
std::string Utilities::escape(std::string &str, bool allow_breaks, bool strip_non_alphanumeric, bool replace_spaces) {

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
            str = removeNonAlphanumeric(str);
        }

        if (replace_spaces) {
            str = removeChar(str, ' ');
        }
    }

    return str;
}

/*
    Escape input everything and remove eveyrthing that isn't a letter

    @param string to escape
    @return fixed string
*/
std::string Utilities::removeNonAlphanumeric(std::string &s) {


    for (std::string::iterator i = s.begin(); i != s.end(); i++) {
        char ch = s.at(i - s.begin());

        if (!isalpha(ch) && !isNumber(std::string(ch + ""))) {
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
std::string Utilities::replaceChar(std::string &s, char ch1, char ch2) {

    for (std::string::iterator i = s.begin(); i != s.end(); i++) {
        if (s.at(i - s.begin()) == ch1)  {
            s[i - s.begin()] = ch2;
            i--;
        }
    }

    return s;
}

/*
    Remove char in string

    @param string to edit
    @param find char to remove
    @return fixed string
*/
std::string Utilities::removeChar(std::string &s, char ch1) {

    for (std::string::iterator i = s.begin(); i != s.end(); i++) {
        if (s.at(i - s.begin()) == ch1) {
            s.erase(i);
            i--;
        }
    }

    return s;
}

/*
    Joins string of vectors with delimeter

    @param vector of strings
    @param delimeter
    @return concatinated string
*/
std::string Utilities::join(std::vector<std::string> strings, std::string delim) {

    if (strings.size() > 0) {
        return std::accumulate(std::next(strings.begin()), strings.end(), strings[0], [delim](std::string a, std::string b) {
            return a + delim + b;
        });
    }
    else {
        return "";
    }
}

/*
	Reads a file line by line

	@param file path
	@return vector of lines
*/
std::vector<std::string> Utilities::readLines(std::string file_path) {

	std::vector<std::string> lines;

	std::ifstream infile(file_path);

	for (std::string line; getline(infile, line); ) {
		lines.push_back(line);
	}

	infile.close();

	return lines;
}

std::string Utilities::base64_encode(const std::string &val) {
	using namespace boost::archive::iterators;
	using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
	auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
	return tmp.append((3 - val.size() % 3) % 3, '=');
}

std::string Utilities::base64_decode(const std::string &val) {
	using namespace boost::archive::iterators;
	using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
	return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), It(std::end(val))), [](char c) {
		return c == '\0';
	});
}