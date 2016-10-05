#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "misc\Configuration.h"
#include "misc\Utilities.h"

/*
    Constructor for Configuration, it will parse it when a new instance of Configuration is created

    @param file path
*/
Configuration::Configuration(string file) : file(file) {
    this->values = new map<string, string>();
    this->parse();
}

/*
    Parse configuration file, it will create the config with default values if nothing
    had been specified

    @return none
*/
void Configuration::parse() {

    if (!ifstream(this->file)) {
        ofstream outputFile;
        outputFile.open(this->file);
        outputFile << "##########################" << endl;
        outputFile << "##     Icarus config    ##" << endl;
        outputFile << "##########################" << endl;
        outputFile << endl;
        outputFile << "database.hostname=127.0.0.1;" << endl;
        outputFile << "database.port=3306;" << endl;
        outputFile << "database.username=user;" << endl;
        outputFile << "database.password=changeme;" << endl;
        outputFile << "database.database=icarus;" << endl;
        outputFile << "database.pool.size=5;" << endl;
        outputFile << endl;
        outputFile << "tcp.server.port=30000;" << endl;
        outputFile << "room.thread.pool.size=4;" << endl;
        outputFile.close();
    }

    ifstream infile(this->file);

    for (string line; getline(infile, line); ) {

        if (line.find("=") != string::npos &&
            line.find(";") != string::npos) {
            line.pop_back(); // remove ';'

            vector<string> split = Utilities::split(line, '=');

            this->values->insert(make_pair(split[0], split[1]));
        }
    }

    infile.close();
}

/*
    Returns string value by given string key

    @param string key to look up value
    @return string value
*/
string Configuration::getString(string key) {

    if (this->values->count(key)) {
        return this->values->find(key)->second;
    }

    return NULL;
}

/*
Returns int value by given string key. attemps to cast from string to int.

@param string key to look up value
@return string value
*/
int Configuration::getInt(string key) {
    if (this->values->count(key)) {
        return stoi(this->values->find(key)->second);
    }

    return NULL;
}

map<string, string> *Configuration::getValues() {
    return this->values;
}

