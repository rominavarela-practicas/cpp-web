#include <iostream>
#include <restclient-cpp/restclient.h>

using namespace std;
int main(int argc, char** argv) {
	string url = argc >= 2 ? argv[1] : "http://www.google.com";
	cout << "requesting " << url << endl;
	RestClient::response r = RestClient::get(url);
	cout << "status code: " << r.code << endl;
	return 0;
}
