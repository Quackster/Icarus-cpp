#pragma once
#include <string>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;


class DatabaseManager {

public:
    DatabaseManager();
    DatabaseManager(string host, string username, string password, string database);
    ~DatabaseManager();
    bool testConnection();
    
private:
    string host;
    string username;
    string password;
    string database;

};