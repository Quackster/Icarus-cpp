#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "misc/Configuration.h"
#include "misc/Utilities.h"

/*
    Constructor for Configuration, it will parse it when a new instance of Configuration is created

    @param file path
*/
Configuration::Configuration(std::string file) : 
    file(file), values(new std::map<std::string, std::string>()) {

    this->parse();
}

/*
    Parse configuration file, it will create the config with default values if nothing
    had been specified

    @return none
*/
void Configuration::parse() {

    if (!std::ifstream(this->file)) {
        std::ofstream output_file;
        output_file.open(this->file);
        output_file << "##########################" << std::endl;
        output_file << "##     Icarus config    ##" << std::endl;
        output_file << "##########################" << std::endl;
        output_file << std::endl;
        output_file << "database.hostname=127.0.0.1;" << std::endl;
        output_file << "database.port=3306;" << std::endl;
        output_file << "database.username=user;" << std::endl;
        output_file << "database.password=changeme;" << std::endl;
        output_file << "database.database=icarus;" << std::endl;
        output_file << "database.pool.size=5;" << std::endl;
        output_file << std::endl;
        output_file << "tcp.server.port=30000;" << std::endl;
        output_file << "thread.pool.size=4;" << std::endl;
        output_file.close();
    }

    std::ifstream infile(this->file);

    for (std::string line; getline(infile, line); ) {

        if (line.find("=") != std::string::npos &&
            line.find(";") != std::string::npos) {
            line.pop_back(); // remove ';'

            std::vector<std::string> split = Utilities::split(line, '=');

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
std::string Configuration::getString(std::string key) {

    if (this->values->count(key)) {
        return this->values->find(key)->second;
    }

    return nullptr;
}

/*
Returns int value by given string key. attemps to cast from string to int.

@param string key to look up value
@return string value
*/
int Configuration::getInt(std::string key) {
    if (this->values->count(key)) {
        return stoi(this->values->find(key)->second);
    }

    return 0;
}

std::map<std::string, std::string> *Configuration::getValues() {
    return this->values;
}

