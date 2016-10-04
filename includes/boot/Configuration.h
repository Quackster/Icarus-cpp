#pragma once
#include <vector>
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
    vector<string> split(const string &s, char delim);

private:
    string file;
    map<string, string> *values;
    void parse();
};

