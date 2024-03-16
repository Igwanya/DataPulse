/*!
 * \file main.cpp
 * Author: Felix Muthui Igwanya
 * email: felixmuthui32@gmail.com
 *
 * \brief Datapulse is a blueprint
 *         session management and data storage in program is
 *         of core struture components to be implemented in
 *         software.
 *
 *  Redis for session managent and mysql or postgres to
 *  store data and for CRUD operations later.
 *
 */
#include <boost/log/trivial.hpp>
/*!
 * Entry point to the program.
 *
 * \param argc an integer arg
 * \param argv an array of arg
 *
 * \return The exit status code of exec
 */
int main(int argc, char **argv)
{
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
    return 0;
}
