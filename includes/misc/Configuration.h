#pragma once
#include <map>
#include <string>

class Configuration
{

public:
    Configuration(std::string file);
    ~Configuration();
    std::string getString(std::string key);
    int getInt(std::string key);
    std::map<std::string, std::string> *getValues();

private:
    std::string file;
    std::map<std::string, std::string> *values;
    void parse();
};

