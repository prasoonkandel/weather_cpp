#include <iostream>
#include <string>
#include <vector>

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

string searchCity(string cityname, string countryname) {
    httplib::Client cli("https://nominatim.openstreetmap.org");

    httplib::Headers headers = {
        { "User-Agent", "weather-app" },
        { "Accept-Language", "en" }
    };
    string path = "/search?q=" + cityname + "," + countryname + "&format=json";

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

void getCords(string cityname, string countryname, vector<double> &cords){
	httplib::Client cli("https://nominatim.openstreetmap.org");
	httplib::Headers headers = {
		{ "User-Agent", "weather-app"},
		{ "Accept-Language", "en"}
 	};

 	string path = "/search?q=" + cityname + "," + countryname + "&format=json";

 	auto res = cli.Get(path.c_str(), headers);

 	if (!res || res->status != 200) {
    	loadingClear();
        cout<<"  Error Fetching Coordinates.\n";
        return;
    }

    json response = json::parse(res->body);

    if(!response.is_array() || response.empty() ){
    	loadingClear();
    	cout<<"  Error Fetching Coordinates.\n";
        return;

    }

    double latitude = stod(response[0]["lat"].get<string>());
    double longitude = stod(response[0]["lon"].get<string>());
    cords.push_back(latitude);
    cords.push_back(longitude);
}

void showWeather(double latitude, double longitude){
    httplib::Client cli("https://api.open-meteo.com");
    httplib::Headers headers = {
        { "User-Agent", "weather-app"},
        { "Accept-Language", "en"}
    };

    string path = "/v1/forecast?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) + "&current_weather=true";

    auto res = cli.Get(path.c_str(), headers);

    if (!res || res->status != 200) {
        loadingClear();
        cout<<"  Error Fetching Weather Data.\n";
        return;
    }

    json response = json::parse(res->body);

    if(response.empty() ){
        loadingClear();
        cout<<"  Error Fetching Weather Data.\n";
        return;

  }
    loadingClear();
    float temperature = response["current_weather"]["temperature"].get<float>();
    string temperature_unit = response["current_weather_units"]["temperature"].get<string>();

    float windspeed = response["current_weather"]["windspeed"].get<float>();
    string windspeed_unit = response["current_weather_units"]["windspeed"].get<string>();

    float winddirection = response["current_weather"]["winddirection"].get<float>();
    string winddirection_unit = response["current_weather_units"]["winddirection"].get<string>();

    string datetime = response["current_weather"]["time"].get<string>();
    string date = datetime.substr(0, 10);
    cout<<"  Date: "<<date<<endl;
    cout<<"  Temperature: "<<temperature<<temperature_unit<<endl;
    cout<<"  Wind Speed: "<<windspeed<<windspeed_unit<<endl;
    cout<<"  Wind Direction: "<<winddirection<<winddirection_unit<<endl;
    weatherCode(4);
}

string weatherCode(int code) {
  switch (code) {
    case 0:
      return "Sunny";
    case 1:
      return "Mostly Sunny";
    case 2:
      return "Partly Cloudy";
    case 3:
      return "Cloudy";
    case 45:
    case 48:
      return "Foggy";
    case 51:
    case 53:
    case 55:
      return "Drizzle";
    case 56:
    case 57:
      return "Freezing Drizzle";
    case 61:
    case 63:
    case 65:
      return "Rain";
    case 66:
    case 67:
      return "Freezing Rain";
    case 71:
    case 73:
    case 75:
      return "Snow";
    case 77:
      return "Snow Grains";
    case 80:
    case 81:
    case 82:
      return "Rain Showers";
    case 85:
    case 86:
      return "Snow Showers";
    case 95:
      return "Thunderstorm";
    case 96:
    case 99:
      return "Thunderstorm & Hail";
    default:
      return "Unknown";
  }
}
