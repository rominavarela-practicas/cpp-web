#include <iostream>
#include <restclient-cpp/restclient.h>

using namespace std;

int main()
{
	string url = "http://localhost:3000";
	string getURL = url+"/get/hello";
	string postURL = url+"/post/something";

	RestClient::response r;

	std::cout << endl << "GET: " << getURL << endl;
	r = RestClient::get(getURL);
	std::cout << "server response: " << r.body << endl;

	std::cout << endl << "POST: " << postURL << endl;
	r = RestClient::post(postURL, "application/json", "{\"foo\": \"bla\"}");
	std::cout << "server response: " << r.body << endl << endl;

	return 0;
}
