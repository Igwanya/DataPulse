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
