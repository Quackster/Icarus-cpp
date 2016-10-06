#include "stdafx.h"
#include "database/DatabaseManager.h"

/*
    Constructor for database manager
*/
DatabaseManager::DatabaseManager(string host, string port, string username, string password, string database, int poolSize) :
    host(host), port(port), username(username), password(password), database(database), poolSize(poolSize){
    this->testedConnection = false;

}

/*
    Tests connection to the database, will attempt to make a pool and store 5 connections, 
    it will print the error if test was unsuccessful.

    This can only be performed once.

    @return if connection is success
*/
bool DatabaseManager::testConnection() {

    try {

        if (this->testedConnection != true) {
            this->testedConnection = true;
            this->mysqlConnectionFactory = new MySQLConnectionFactory(this->host, this->port, this->username, this->password, this->database);
            this->mysqlPool = new ConnectionPool<MySQLConnection>(this->poolSize, this->mysqlConnectionFactory);
            
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
    
    if (this->testedConnection) {
        delete this->mysqlConnectionFactory;
        delete this->mysqlPool;
    }
}