// see https://github.com/acmorrow/dslam
// client example http://stackoverflow.com/questions/14601100/http-client-request-response-with-pion-net-c
#include <iostream>
#include <cstdlib>//legacy stdlib.h and time.h
#include <ctime>

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <pion/http/request.hpp>
#include <pion/http/request_writer.hpp>

using namespace std;
using namespace pion;

int main()
{
	std::cout << "!!!Hello World!!!" << endl;
	//pion::http::request::request 	r;
	//pion::http::request::request* httpRequest_ptr =
	//new request("http://localhost:3000");

	//pion::http::request_ptr ptr;
	http::request r = pion::http::request_writer::get_request();
	return 0;
}
