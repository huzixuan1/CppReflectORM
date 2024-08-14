#ifndef CONNECTIONS_DB_HPP
#define CONNECTIONS_DB_HPP

#include <memory>
#include <string>
#include <iostream>

using namespace std;


class DatabaseConnection {
public:
    virtual ~DatabaseConnection() {}
    virtual void connect() const = 0;
};


class MySqlConnection : public DatabaseConnection {
public:
    static MySqlConnection& getInstance() {
        static MySqlConnection instance;
        return instance;
    }
    void connect() const override {
        std::cout << "connected to Mysql database." << std::endl;
    }
};


class MariadbSqlconnection : public DatabaseConnection {
public:
    static MariadbSqlconnection& getInstance(){
        static MariadbSqlconnection instance;
        return instance;
    }
    void connect() const override {
        std::cout << "connected to Mariadb database." << std::endl;
    }
};

class ConnectionFactory {
public:
    static std::shared_ptr<DatabaseConnection> createConnection(const std::string& dbType) {
        if (dbType == "Mysql") {
            static std::shared_ptr<MySqlConnection> mysqlConnection = std::make_shared<MySqlConnection>(MySqlConnection::getInstance());
            return mysqlConnection;
        } else if (dbType == "Mariadb") {
            static std::shared_ptr<MariadbSqlconnection> mariadbConnetion = std::make_shared<MariadbSqlconnection>(MariadbSqlconnection::getInstance());
            return mariadbConnetion;
        } else {
            throw std::invalid_argument("unsupported database type");
        }
    }
};

// int main() {
//     std::shared_ptr<DatabaseConnection> mysqlConnection1 = ConnectionFactory::createConnection("Mysql");
//     mysqlConnection1->connect();

//     std::shared_ptr<DatabaseConnection> mysqlConnection2 = ConnectionFactory::createConnection("Mysql");
//     mysqlConnection2->connect();

//     if (mysqlConnection1.get() == mysqlConnection2.get()) {
//         std::cout << "mysqlConnection1 and mysqlConnection2 are the same object." << std::endl;
//     } else {
//         std::cout << "mysqlConnection1 and mysqlConnection2 are different objects." << std::endl;
//     }
   
//     return 0;
// }

#endif // CONNECTIONS_DB_HPP
