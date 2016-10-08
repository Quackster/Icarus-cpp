#pragma once
#include <string>
#include <cppconn/exception.h>

#include "mysql_connection.h"
#include "database/lib/MySQLConnection.h"

class DatabaseManager {

public:
    DatabaseManager(std::string host, std::string port, std::string username, std::string password, std::string database, int poolSize);
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
    int poolSize;
    
    MySQLConnectionFactory *mysql_connection_factory;
    ConnectionPool<MySQLConnection> *mysql_pool;

};