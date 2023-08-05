#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/mysql.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/system/system_error.hpp>
#include <boost/log/trivial.hpp>

#include <iostream>
#include <string>

class Connection
{
public:
    Connection();

    ~Connection();

    void intiialise_tables(boost::mysql::tcp_ssl_connection &conn);

    void drop_tests_tables();

private:
    std::string _username = "root";
    std::string _password = "Igwanya32*";
    std::string _database = "boost_mysql";
};

#endif // CONNECTION_H
