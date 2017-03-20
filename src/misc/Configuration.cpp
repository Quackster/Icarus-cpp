/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include <fstream>
#include <sstream>
#include <thread>

#include "Configuration.h"
#include "Utilities.h"

/*
    Constructor for Configuration, it will parse it when a new instance of Configuration is created

    @param file path
*/
Configuration::Configuration(std::string file) : 
    file(file) {
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

        /*Icarus::database_configuration = new Configuration("logs/database.ini");
        Icarus::game_configuration = new Configuration("logs/game.ini");
        Icarus::server_configuration = new Configuration("logs/server.ini");
        Icarus::log_configuration = new Configuration("logs/log.ini");*/

        if (this->file == "config/database.ini") {
            output_file << endl;
            output_file << "############################" << endl;
            output_file << "##     Database config    ##" << endl;
            output_file << "############################" << endl;
            output_file << endl;
            output_file << "database.hostname=127.0.0.1;" << endl;
            output_file << "database.port=3306;" << endl;
            output_file << "database.username=user;" << endl;
            output_file << "database.password=changeme;" << endl;
            output_file << "database.database=icarus;" << endl;
            output_file << "database.pool.size=5;" << endl;
        }

        if (this->file == "config/log.ini") {
            output_file << endl;
            output_file << "##########################" << endl;
            output_file << "##    Logging config    ##" << endl;
            output_file << "##########################" << endl;
            output_file << endl;
            output_file << "log.player.connect=true;" << endl;
            output_file << "log.player.disconnect=true;" << endl;
            output_file << endl;
            output_file << "log.message.handled=false;" << endl;
            output_file << "log.message.unhandled=false;" << endl;
            output_file << endl;
            output_file << "log.room.loaded=true;" << endl;
            output_file << "log.room.unloaded=true;" << endl;
            output_file << endl;
            output_file << "log.network.rawpacket=false;" << endl;
        }

        if (this->file == "config/server.ini") {
            output_file << endl;
            output_file << "#######################" << endl;
            output_file << "##     TCP server    ##" << endl;
            output_file << "#######################" << endl;
            output_file << endl;
            output_file << "tcp.server.host=0.0.0.0;" << endl;
            output_file << "tcp.server.port=30000;" << endl;
            output_file << endl;
            output_file << "########################" << endl;
            output_file << "##     RCON server    ##" << endl;
            output_file << "########################" << endl;
            output_file << endl;
            output_file << "rcon.server.host=0.0.0.0;" << endl;
            output_file << "rcon.server.port=3902;" << endl;
            output_file << "rcon.server.password=alexthebest;" << endl;
        }

        if (this->file == "config/game.ini") {

            int processors = std::thread::hardware_concurrency();

            if (processors == 0) {
                processors = 8;
            }
            else {
                processors = processors * 2;
            }

            output_file << endl;
            output_file << "########################" << endl;
            output_file << "##     Game config    ##" << endl;
            output_file << "########################" << endl;
            output_file << endl;
            output_file << "game.revision=PRODUCTION-201512012203-525044429;" << endl;
            output_file << endl;
            output_file << "thread.pool.size=" << processors << ";" << endl;
            output_file << endl;
            output_file << "chat.flood.max=5;" << endl;
            output_file << "chat.flood.seconds=4;" << endl;
            output_file << "chat.flood.wait=20;" << endl;
            output_file << endl;
            output_file << "room.idle.seconds=300;" << endl;
            output_file << endl;
            output_file << "newuser.create.newbie.room=false;" << endl;
        }

        output_file.close();
    }

    std::ifstream infile(this->file);

    for (std::string line; getline(infile, line); ) {

        if (line.find("=") != std::string::npos &&
            line.find(";") != std::string::npos) {
            line.pop_back(); // remove ';'

            std::vector<std::string> split = Utilities::split(line, '=');

            this->values.insert(make_pair(split[0], split[1]));
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

    if (this->values.count(key)) {
        return this->values.find(key)->second;
    }

    return "";
}

/*
    Returns boolean value by given string key

    @param string key to look up value
    @return boolean value
*/
bool Configuration::getBool(std::string key) {

    if (this->values.count(key)) {
        return this->values.find(key)->second == "true";
    }

    return nullptr;
}

/*
    Returns int value by given string key. attemps to cast from string to int.

    @param string key to look up value
    @return string value
*/
int Configuration::getInt(std::string key) {
    if (this->values.count(key)) {
        return stoi(this->values.find(key)->second);
    }

    return 0;
}

std::map<std::string, std::string> Configuration::getValues() {
    return this->values;
}

