#pragma once
#include <map>
#include <string>

using namespace std;

class Configuration
{

public:
    Configuration(string file);
    ~Configuration();
    string getString(string key);
    int getInt(string key);
    map<string, string> *getValues();

private:
    string file;
    map<string, string> *values;
    void parse();
};

