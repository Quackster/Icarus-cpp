#include "database/DatabaseManager.h"
#include <cppconn/exception.h>

DatabaseManager::DatabaseManager() {

}

DatabaseManager::DatabaseManager(string host, string username, string password, string database) :
    host(host), username(username), password(password), database(database) {

}

bool DatabaseManager::testConnection() {

    try {
        sql::Driver *driver = nullptr;
        sql::Connection *con = nullptr;

        driver = get_driver_instance();

        con = driver->connect(this->host, this->username, this->password);
        con->setSchema(this->database);
    }
    catch (sql::SQLException &e) {
        cout << endl;
        cout << " [ERROR] SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << " [ERROR] Message: " << e.what() << endl;
        cout << " [ERROR] Error code: " << e.getErrorCode() << endl;
        cout << " [ERROR] SQLState: " << e.getSQLState() << endl;
        cout << endl;
        return false;
    }

    return true;
}

DatabaseManager::~DatabaseManager() {


}