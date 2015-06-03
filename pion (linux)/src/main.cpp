// see https://github.com/acmorrow/dslam
// client example http://stackoverflow.com/questions/14601100/http-client-request-response-with-pion-net-c
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
//#include <boost/any.hpp>

#include <pion/http/request.hpp>
#include <pion/http/types.hpp>

using namespace std;
using namespace pion;

int main()
{
	std::cout << "!!!Hello World!!!" << endl;

	pion::http::request r("http://localhost:3000");
	r.set_method(pion::http::types::REQUEST_METHOD_GET);


	return 0;
}

/*
pion::http::request request;
std::string requestData = "";
request.set_content(requestData);
httpClient client(boost::asio::ip::address::from_string("127.0.0.1"), 3000);
pion::http::response_ptr response;
boost::system::error_code ec;
response = client.blockingReceiveOrTimeout(request, ec);
response->write(std::cout, ec);
return 0;
*/
