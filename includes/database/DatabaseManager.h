#pragma once
#include <string>
#include <cppconn/exception.h>

#include "mysql_connection.h"
#include "database/lib/MySQLConnection.h"



using namespace std;


class DatabaseManager {

public:
    DatabaseManager();
    DatabaseManager(string host, string username, string password, string database);
    ~DatabaseManager();
    bool testConnection();
    void printException(sql::SQLException &e);
    
private:
    string host;
    string username;
    string password;
    string database;
    
    MySQLConnectionFactory *mysql_connection_factory;
    ConnectionPool<MySQLConnection> *mysql_pool;

};