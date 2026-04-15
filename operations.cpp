#include <iostream>
#include <string>
#include <vector>
#include <limits>

#define CPPHTTPLIB_OPENSSL_SUPPORT

//Including Operations Header File
#include "operations.hpp"

//Including External Libraries
#include "external/httplib.h"
#include "external/json.hpp"

using namespace std; 
using json = nlohmann::json;

//Margin Function
void margin(){
	cout<<"==================================================================="<<endl;
}
//Loading Functions

void loading() {
    cout << "  Loading..." << flush;
}

void loadingClear() {
    cout << "\r               \r" << flush;
}

//Various Operations

string searchCity(string city, string country) {
    httplib::Client cli("https://nominatim.openstreetmap.org");

    httplib::Headers headers = {
        { "User-Agent", "weather-app" },
        { "Accept-Language", "en" }
    };
    string path = "/search?q=" + city + "," + country + "&format=json";

    auto res = cli.Get(path.c_str(), headers);

    if (!res || res->status != 200) {
    	loadingClear();
        cout << "  HTTP error\n"; 
        return "";
    }

    json response = json::parse(res->body);

    if (!response.is_array() || response.empty()) {
        loadingClear();
        cout << "  No results\n";
        return "";
    }

    return response[0]["display_name"];
}