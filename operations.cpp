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

class Location{
    private:
        double latitude;
        double longitude;
};
//Margin Function
void margin(){
	cout<<"\033[32m===================================================================\033[0m"<<endl;
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
        cout<<"\033[1;31m  Error Fetching Coordinates.\033[0m\n";
        return;
    }

    json response = json::parse(res->body);

    if(!response.is_array() || response.empty() ){
    	loadingClear();
    	cout<<"\033[1;31m  Error Fetching Coordinates.\033[0m\n";
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

    string path = "/v1/forecast?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) + "&current=temperature_2m,relative_humidity_2m,wind_speed_10m,wind_direction_10m,weather_code";

    auto res = cli.Get(path.c_str(), headers);

    if (!res || res->status != 200) {
        loadingClear();
        cout<<"\033[1;31m  Error Fetching Weather Data.\033[0m\n";
        return;
    }

    json response = json::parse(res->body);

    if(response.empty() ){
        loadingClear();
        cout<<"\033[1;31m  Error Fetching Weather Data.\033[0m\n";
        return;

  }
    loadingClear();
    float temperature = response["current"]["temperature_2m"].get<float>();
    string temperature_unit = response["current_units"]["temperature_2m"].get<string>();

    float windspeed = response["current"]["wind_speed_10m"].get<float>();
    string windspeed_unit = response["current_units"]["wind_speed_10m"].get<string>();

    float winddirection = response["current"]["wind_direction_10m"].get<float>();
    string winddirection_unit = response["current_units"]["wind_direction_10m"].get<string>();

    string datetime = response["current"]["time"].get<string>();
    string date = datetime.substr(0, 10);

    int weather_code = response["current"]["weather_code"].get<int>();
    string weather = weatherCode(weather_code);
    cout<<"  Date: "<<date<<endl;
    cout<<"  Temperature: "<<temperature<<temperature_unit<<endl;
    cout<<"  Weather: "<<weather<<endl;
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
      return "\033[1;31m Unknown \033[0m";
  }
}
