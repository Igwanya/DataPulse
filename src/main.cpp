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

#include <iostream>
#include <limits>
#include <boost/log/trivial.hpp>

int64_t
factorial(int64_t);

void
swap(int* x, int* y);

 /*!
 * 
  * Entry point to the program.
  *
  * \param argc an integer arg
  * \param argv an array of arg
  *
  * \return The exit status code of exec
  */
int main(int argc, char** argv)
{
	int arg_num{ argc };
	char** arg_v = { argv };
	int x{ 3 };
	int y{ 5 };
	swap(&x, &y);
	BOOST_LOG_TRIVIAL(debug) << factorial(3);
	BOOST_LOG_TRIVIAL(debug) << "swap_func: x=" << x << " y= " << y;
	return EXIT_SUCCESS;
}

int64_t
factorial(int64_t n)
{
	if (n <= 1)
		return 1;
	return n * factorial(n - 1); // 6 30
}

void
swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}