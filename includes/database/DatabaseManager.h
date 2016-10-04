#pragma once
#include <string>
#include <cppconn/exception.h>

#include "mysql_connection.h"
#include "database/lib/MySQLConnection.h"



using namespace std;


class DatabaseManager {

public:
    DatabaseManager(string host, string port, string username, string password, string database);
    ~DatabaseManager();
    bool testConnection();
    void printException(sql::SQLException &e);
    
private:
    string host;
    string port;
    string username;
    string password;
    string database;
    bool tested_connection;
    
    MySQLConnectionFactory *mysql_connection_factory;
    ConnectionPool<MySQLConnection> *mysql_pool;

};