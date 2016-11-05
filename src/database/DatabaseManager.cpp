/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "database/DatabaseManager.h"

/*
    Constructor for database manager
*/
DatabaseManager::DatabaseManager(std::string host, std::string port, std::string username, std::string password, std::string database, int pool_size) :
    host(host), 
    port(port), 
    username(username), 
    password(password), 
    database(database), 
    pool_size(pool_size), 
    tested_connection(false),
    mysql_connection_factory(nullptr),
    mysql_pool(nullptr) { }

/*
    Tests connection to the database, will attempt to make a pool and store 5 connections, 
    it will print the error if test was unsuccessful.

    This can only be performed once.

    @return if connection is success
*/
bool DatabaseManager::testConnection() {

    try {

        if (this->tested_connection != true) {
            this->tested_connection = true;
            this->mysql_connection_factory = new MySQLConnectionFactory(this->host, this->port, this->username, this->password, this->database);
            this->mysql_pool = new ConnectionPool<MySQLConnection>(this->pool_size, this->mysql_connection_factory);
            
        }
    }
    catch (sql::SQLException &e) {
        this->printException(e, __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    return true;
}        

/*
    Prints SQL exception for easy reading

    @param exception reference
    @param __FILE__
    @param __FUNCTION__
    @param __LINE__
    @return none
*/
void DatabaseManager::printException(sql::SQLException &e, char* file, char* function, int line) {
    std::cout << std::endl << " [ERROR] SQLException in " << file << "(" << function << ") on line " << line << std::endl;
    std::cout << " [ERROR] Message: " << e.what() << std::endl;
    std::cout << " [ERROR] Error code: " << e.getErrorCode() << std::endl;
    std::cout << " [ERROR] SQLState: " << e.getSQLState() << std::endl;
    std::cout << std::endl;

    std::string message = e.what();

    if (message.find("has gone away") != std::string::npos) {
        
        if (mysql_connection_factory != nullptr) {
            delete this->mysql_connection_factory;
            this->mysql_connection_factory = new MySQLConnectionFactory(this->host, this->port, this->username, this->password, this->database);
        }

        if (mysql_pool != nullptr) {
            delete this->mysql_pool;
            this->mysql_pool = new ConnectionPool<MySQLConnection>(this->pool_size, this->mysql_connection_factory);
        }
    }
}

/*
    Database manager deconstructor
*/
DatabaseManager::~DatabaseManager() {
    
    if (this->tested_connection) {
        delete this->mysql_connection_factory;
        delete this->mysql_pool;
    }
}