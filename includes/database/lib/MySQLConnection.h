/* Copyright 2013 Active911 Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http: *www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "ConnectionPool.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>

class MySQLConnection : public Connection {

public:
	~MySQLConnection() {
		if (this->sql_connection) {
			this->sql_connection->close();
			this->sql_connection.reset(); 	// Release and destruct	
		}
	};

	std::shared_ptr<sql::Connection> sql_connection;
	int a;
};


class MySQLConnectionFactory : public ConnectionFactory {

public:
	MySQLConnectionFactory(std::string server, std::string port, ::string username, std::string password, std::string database) {
        this->server = "tcp://" + server + ":" + port;
		this->username=username;
		this->password=password;
        this->database = database;

	};

	// Any exceptions thrown here should be caught elsewhere
    std::shared_ptr<Connection> create() {

		// Get the driver
		sql::Driver *driver = get_driver_instance();

        // Create the connection
        shared_ptr<MySQLConnection>conn(new MySQLConnection());

        // Connect
        conn->sql_connection = std::shared_ptr<sql::Connection>(driver->connect(this->server, this->username, this->password));
        conn->sql_connection->setSchema(this->database);

		return std::static_pointer_cast<Connection>(conn);
	};

private:
	std::string server;
	std::string username;
	std::string password;
    std::string database;
};