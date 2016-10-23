/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>
#include <cppconn/exception.h>

#include "mysql_connection.h"
#include "database/lib/MySQLConnection.h"

class DatabaseManager {

public:
    DatabaseManager(std::string host, std::string port, std::string username, std::string password, std::string database, int pool_size);
    ~DatabaseManager();
    bool testConnection();
    void printException(sql::SQLException &e, char* file, char* function, int line);

    MySQLConnectionFactory *getConnectionFactory() { return this->mysql_connection_factory; }
    ConnectionPool<MySQLConnection> *getConnectionPool() { return this->mysql_pool; }

private:
    std::string host;
    std::string port;
    std::string username;
    std::string password;
    std::string database;
    bool tested_connection;
    int pool_size;
    
    MySQLConnectionFactory *mysql_connection_factory;
    ConnectionPool<MySQLConnection> *mysql_pool;

};