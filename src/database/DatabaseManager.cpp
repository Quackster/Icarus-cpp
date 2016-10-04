#include "stdafx.h"
#include "database/DatabaseManager.h"

/*
    Constructor for database manager
*/
DatabaseManager::DatabaseManager(string host, string port, string username, string password, string database, int pool_size) :
    host(host), port(port), username(username), password(password), database(database), pool_size(pool_size){
    this->tested_connection = false;

}

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
    cout << endl << " [ERROR] SQLException in " << file << "(" << function << ") on line " << line << endl;
    cout << " [ERROR] Message: " << e.what() << endl;
    cout << " [ERROR] Error code: " << e.getErrorCode() << endl;
    cout << " [ERROR] SQLState: " << e.getSQLState() << endl;
    cout << endl;
}

/*
    Database manager deconstructor
*/
DatabaseManager::~DatabaseManager() {
    
    if (tested_connection) {
        delete this->mysql_connection_factory;
        delete this->mysql_pool;
    }
}