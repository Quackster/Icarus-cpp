/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <map>
#include <string>

class Configuration
{

public:
    Configuration(std::string file);
    //~Configuration();
    std::string getString(std::string key);
    int getInt(std::string key);
    std::map<std::string, std::string> *getValues();

private:
    std::string file;
    std::map<std::string, std::string> *values;
    void parse();
};

