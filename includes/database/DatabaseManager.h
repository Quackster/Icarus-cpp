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

    MySQLConnectionFactory *getConnectionFactory() { return this->mysqlConnectionFactory; }
    ConnectionPool<MySQLConnection> *getConnectionPool() { return this->mysqlPool; }

private:
    std::string host;
    std::string port;
    std::string username;
    std::string password;
    std::string database;
    bool testedConnection;
    int poolSize;
    
    MySQLConnectionFactory *mysqlConnectionFactory;
    ConnectionPool<MySQLConnection> *mysqlPool;

};