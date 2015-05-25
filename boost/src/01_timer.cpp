#include <iostream>
#include <cstdlib>//legacy stdlib.h and time.h
#include <ctime>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

int main()
{
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io,boost::posix_time::seconds(5));
	std::cout << "5 secs..." << endl;
  t.wait();
	std::cout << "!!!Hello World!!!" << endl;
	return 0;
}
