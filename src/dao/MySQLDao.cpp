#pragma once
#include "stdafx.h"
#include "dao/MySQLDao.h"
#include "boot/Icarus.h"

/*
   Returns true/false if a query has rows existing

    @param sql query
    @return bool
*/

bool MySQLDao::exists(std::string query) {

    bool output = false;
    std::shared_ptr<MySQLConnection> connection = Icarus::getDatabaseManager()->getConnectionPool()->borrow();

    try {
        std::shared_ptr<sql::Connection> sql_connection = connection->sql_connection;
        std::shared_ptr<sql::Statement> statement = std::shared_ptr<sql::Statement>(sql_connection->createStatement());
        std::shared_ptr<sql::ResultSet> result_set = std::shared_ptr<sql::ResultSet>(statement->executeQuery(query));
        output = result_set->next();
    }
    catch (sql::SQLException &e) {
        Icarus::getDatabaseManager()->printException(e, __FILE__, __FUNCTION__, __LINE__);
    }

    Icarus::getDatabaseManager()->getConnectionPool()->unborrow(connection);

    return output;
}
