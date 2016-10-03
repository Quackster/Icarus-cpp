#include "database/DatabaseManager.h"

DatabaseManager::DatabaseManager() {

}

DatabaseManager::DatabaseManager(string host, string username, string password, string database) :
    host(host), username(username), password(password), database(database) {

}

bool DatabaseManager::testConnection() {

    try {
        this->mysql_connection_factory = new MySQLConnectionFactory(this->host, this->username, this->password, this->database);
        this->mysql_pool = new ConnectionPool<MySQLConnection>(5, mysql_connection_factory);

        /*shared_ptr<MySQLConnection> conn = mysql_pool->borrow();
        std::shared_ptr<sql::Statement> stmt = std::shared_ptr<sql::Statement>(conn->sql_connection->createStatement());
        stmt->execute("INSERT INTO testing (id) VALUES (1)");
        mysql_pool->unborrow(conn);*/
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


}