#pragma once
#include <string>
#include <cppconn/exception.h>

#include "mysql_connection.h"
#include "database/lib/MySQLConnection.h"



using namespace std;


class DatabaseManager {

public:
    DatabaseManager(string host, string port, string username, string password, string database, int poolSize);
    ~DatabaseManager();
    bool testConnection();
    void printException(sql::SQLException &e, char* file, char* function, int line);

    MySQLConnectionFactory *getConnectionFactory() { return this->mysqlConnectionFactory; }
    ConnectionPool<MySQLConnection> *getConnectionPool() { return this->mysqlPool; }

private:
    string host;
    string port;
    string username;
    string password;
    string database;
    bool testedConnection;
    int poolSize;
    
    MySQLConnectionFactory *mysqlConnectionFactory;
    ConnectionPool<MySQLConnection> *mysqlPool;

};