#include "stdafx.h"
#include "database/DatabaseManager.h"


DatabaseManager::DatabaseManager(string host, string port, string username, string password, string database) :
    host(host), port(port), username(username), password(password), database(database) {

}

bool DatabaseManager::testConnection() {

    try {

        if (!tested_connection) {
            this->mysql_connection_factory = new MySQLConnectionFactory(this->host, this->port, this->username, this->password, this->database);
            this->mysql_pool = new ConnectionPool<MySQLConnection>(5, mysql_connection_factory);
            this->tested_connection = true;
        }
    }
    catch (sql::SQLException &e) {
        cout << endl << " [ERROR] SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        this->printException(e);
        return false;
    }

    return true;
}        

void DatabaseManager::printException(sql::SQLException &e) {
    cout << " [ERROR] Message: " << e.what() << endl;
    cout << " [ERROR] Error code: " << e.getErrorCode() << endl;
    cout << " [ERROR] SQLState: " << e.getSQLState() << endl;
    cout << endl;
}

DatabaseManager::~DatabaseManager() {
    
    if (tested_connection) {
        delete this->mysql_connection_factory;
        delete this->mysql_pool;
    }
}