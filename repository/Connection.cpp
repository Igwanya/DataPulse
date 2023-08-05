#include "Connection.h"

Connection::Connection()
{
    try
    {
        // The execution context, required to run I/O operations.
        boost::asio::io_context ctx;

        // The SSL context, required to establish TLS connections.
        // The default SSL options are good enough for us at this point.
        boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);

        // Represents a connection to the MySQL server.
        boost::mysql::tcp_ssl_connection conn(ctx.get_executor(), ssl_ctx);

        // Resolve the hostname to get a collection of endpoints
        boost::asio::ip::tcp::resolver resolver(ctx.get_executor());
        auto endpoints = resolver.resolve("localhost", boost::mysql::default_port_string);

        // The username, password and database to use
        boost::mysql::handshake_params params(
            _username, // username
            _password, // password
            _database  // database
            );

        // Connect to the server using the first endpoint returned by the resolver
        conn.connect(*endpoints.begin(), params);

        // Issue the SQL query to the server
        const char* sql = "SELECT 'Hello world!'";
        boost::mysql::results result;
        conn.query(sql, result);

        // Print the first field in the first row
        BOOST_LOG_TRIVIAL(debug) << result.rows().at(0).at(0) << std::endl;
        BOOST_LOG_TRIVIAL(debug) << "Initialising application tables. \n";
        intiialise_tables(conn);

        // Close the connection
        conn.close();
    }
    catch (const boost::mysql::error_with_diagnostics& err)
    {
        // Some errors include additional diagnostics, like server-provided error messages.
        // Security note: diagnostics::server_message may contain user-supplied values (e.g. the
        // field value that caused the error) and is encoded using to the connection's encoding
        // (UTF-8 by default). Treat is as untrusted input.
        BOOST_LOG_TRIVIAL(error) << "Error: " << err.what() << '\n'
                                 << "Server diagnostics: " << err.get_diagnostics().server_message() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception& err)
    {
        BOOST_LOG_TRIVIAL(error) << "Error: " << err.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }

}


void Connection::intiialise_tables(boost::mysql::tcp_ssl_connection &conn)
{
    std::string sql_crate_user_table =
        "CREATE TABLE `boost_mysql`.`Users` ( `id` INT NOT NULL AUTO_INCREMENT , `title` VARCHAR(100) NULL DEFAULT NULL , `surname` VARCHAR(200) NULL DEFAULT NULL , `fullNames` VARCHAR(200) NULL DEFAULT NULL , `studentEmailAddress` VARCHAR(250) NULL DEFAULT NULL , `registrationNumber` VARCHAR(250) NULL DEFAULT NULL , `role` VARCHAR(200) NULL DEFAULT NULL , `profilePhotoURL` VARCHAR(200) NULL DEFAULT NULL , PRIMARY KEY (`id`)) ENGINE = InnoDB; ";

    std::string sql_crate_user_table_tests =
        "CREATE TABLE `boost_mysql`.`Users_tests` ( `id` INT NOT NULL AUTO_INCREMENT , `title` VARCHAR(100) NULL DEFAULT NULL , `surname` VARCHAR(200) NULL DEFAULT NULL , `fullNames` VARCHAR(200) NULL DEFAULT NULL , `studentEmailAddress` VARCHAR(250) NULL DEFAULT NULL , `registrationNumber` VARCHAR(250) NULL DEFAULT NULL , `role` VARCHAR(200) NULL DEFAULT NULL , `profilePhotoURL` VARCHAR(200) NULL DEFAULT NULL , PRIMARY KEY (`id`)) ENGINE = InnoDB; ";


    boost::mysql::results result;
    conn.query(sql_crate_user_table, result);

    conn.query(sql_crate_user_table_tests, result);

    // Print the first field in the first row
    BOOST_LOG_TRIVIAL(debug) <<" User table created and the test table " << std::endl;
}

void Connection::drop_tests_tables()
{
    try
    {
        // The execution context, required to run I/O operations.
        boost::asio::io_context ctx;

        // The SSL context, required to establish TLS connections.
        // The default SSL options are good enough for us at this point.
        boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);

        // Represents a connection to the MySQL server.
        boost::mysql::tcp_ssl_connection conn(ctx.get_executor(), ssl_ctx);

        // Resolve the hostname to get a collection of endpoints
        boost::asio::ip::tcp::resolver resolver(ctx.get_executor());
        auto endpoints = resolver.resolve("localhost", boost::mysql::default_port_string);

        // The username, password and database to use
        boost::mysql::handshake_params params(
            _username, // username
            _password, // password
            _database  // database
            );

        // Connect to the server using the first endpoint returned by the resolver
        conn.connect(*endpoints.begin(), params);

        // Issue the SQL query to the server
        const char* sql = "Drop TABLE Users_tests;";
        boost::mysql::results result;
        conn.query(sql, result);

        // Print the first field in the first row
        BOOST_LOG_TRIVIAL(debug) <<"Drop user test table :" << result.rows().at(0).at(0) << std::endl;

        intiialise_tables(conn);

        // Close the connection
        conn.close();
    }
    catch (const boost::mysql::error_with_diagnostics& err)
    {
        // Some errors include additional diagnostics, like server-provided error messages.
        // Security note: diagnostics::server_message may contain user-supplied values (e.g. the
        // field value that caused the error) and is encoded using to the connection's encoding
        // (UTF-8 by default). Treat is as untrusted input.
        BOOST_LOG_TRIVIAL(error) << "Error: " << err.what() << '\n'
                                 << "Server diagnostics: " << err.get_diagnostics().server_message() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (const std::exception& err)
    {
        BOOST_LOG_TRIVIAL(error) << "Error: " << err.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
