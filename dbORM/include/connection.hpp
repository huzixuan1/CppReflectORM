#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <iostream>

// g++ connect.cpp -o connect -I/usr/include/mysql -lmysqlcppconn

// SELECT User, Host FROM mysql.user;

// sudo service mysql start
// sudo mysql -uroot -p

// mysql> GRANT ALL PRIVILEGES ON *.* TO 'user'@'%'IDENTIFIED BY 'password' WITH GRANT OPTION;
// ERROR 1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'IDENTIFIED BY 'password' WITH GRANT OPTION' at line 1
// mysql> CREATE USER 'taotao'@'%' IDENTIFIED BY 'password';
// Query OK, 0 rows affected (0.02 sec)

// mysql> GRANT ALL PRIVILEGES ON *.* TO 'user'@'%' WITH GRANT OPTION;
// Query OK, 0 rows affected (0.01 sec)

// mysql> FLUSH PRIVILEGES;
// Query OK, 0 rows affected (0.03 sec)

// cd /etc/mysql/mysql.conf.d
// vim mysqld.cnf
// check port

// reference:https://blog.csdn.net/hexf9632/article/details/103890046

namespace connectionAction
{

    sql::Connection *connectDB(const std::string &host, const std::string &user,
                               const std::string &passwd, const std::string &database)
    {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection *con = nullptr;

        try
        {
            con = driver->connect(host, user, passwd);
            con->setSchema(database);
            std::cout << "Connected to database successfully!" << std::endl;
        }
        catch (sql::SQLException &e)
        {
            std::cerr << "Error connecting to database: " << e.what() << std::endl;
            delete con;
            return nullptr;
        }

        return con;
    }

    void action()
    {
        const std::string host = "tcp://127.0.0.1:3307";
        const std::string user = "taotao";
        const std::string passwd = "password";
        const std::string database = "new_database";

        sql::Connection *connection = connectDB(host, user, passwd, database);
        if (connection)
        {

        } // if
    }

}

#endif // CONNECTION_HPP