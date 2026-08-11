#include <iostream>
#include <stdexcept>
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT

//Including Operations Header File
#include "operations.hpp"

//Including External Libraries
#include "external/httplib.h"
#include "external/json.hpp"

using namespace std;
using json = nlohmann::json;

//Utility Functions
void margin(){
	cout<<"\033[32m===================================================================\033[0m"<<endl;
}

void loading() {
    cout << "  Loading..." << flush;
}

void loadingClear() {
    cout << "\r               \r" << flush;
}

void clearScreen() {
    std::cout << "\033[H\033[2J" << std::flush;
}

//Message Functions
void errorMessage(std::string message, bool newLine){
    if(newLine){
    cout<<"\033[1;31m"<<"  "<<message<<"\033[0m"<<endl;
    }
    else{
    cout<<"\033[1;31m"<<"  "<<message<<"\033[0m";
    }
}
//Location Class Method
Location::Location(std::string query){
    this->query = query;
    fetched = false;

}

double Location::getLatitude(){
    if(!fetched){
        throw runtime_error("Location not fetched");
    }
    return this-> latitude;
}

double Location::getLongitude(){
    if(!fetched){
        throw runtime_error("Location not fetched");
    }
    return this-> longitude;
}

string Location::getDisplayName(){
    if(!fetched){
        throw runtime_error("Location not fetched");
    }
    return this-> display_name;
}
void Location::searchLocation(){
httplib::Client cli("https://nominatim.openstreetmap.org");

httplib::Headers headers = {
{ "User-Agent", "weather-app" },
{ "Accept-Language", "en" }
};
string path = "/search?q=" + this->query + "&format=json";

auto res = cli.Get(path.c_str(), headers);

if (!res || res->status != 200) {
loadingClear();
errorMessage("HTTP Error", 1);
return;
}

json response = json::parse(res->body);

if (!response.is_array() || response.empty()) {
loadingClear();
errorMessage("No results", 1);
return;
}

this->display_name = response[0]["display_name"];
}

void Location::fetchCords(){

string display_name = this->display_name;

httplib::Client cli("https://nominatim.openstreetmap.org");
httplib::Headers headers = {
{ "User-Agent", "weather-app"},
{ "Accept-Language", "en"}
};


string path = "/search?q=" + display_name + "&format=json";

auto res = cli.Get(path.c_str(), headers);

json response = json::parse(res->body);

if(!response.is_array() || response.empty() ){
loadingClear();
cout<<"\033[1;31m Error Fetching Coordinates.\033[0m\n";
return;

}

this->latitude = stod(response[0]["lat"].get<string>());
this->longitude = stod(response[0]["lon"].get<string>());
fetched = true;
}

//Weather Class Methods
Weather::Weather(Location location){
        try{
        latitude = location.getLatitude();
        longitude = location.getLongitude();
        }
        catch(runtime_error& e){
            errorMessage(e.what(), 1);
        }
        fetched = false;
}

void Weather::fetchWeather(){
    httplib::Client cli("https://api.open-meteo.com");
    httplib::Headers headers = {
        { "User-Agent", "weather-app"},
        { "Accept-Language", "en"}
    };

    string path = "/v1/forecast?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) + "&current=temperature_2m,relative_humidity_2m,wind_speed_10m,wind_direction_10m,weather_code";

    auto res = cli.Get(path.c_str(), headers);

    if (!res || res->status != 200) {
        loadingClear();
        cout<<"\033[1;31m  \033[0m\n";
        errorMessage("Error Fetching Weather Data.", 1);
        return;
    }

    json response = json::parse(res->body);

    if(response.empty() ){
        loadingClear();
        errorMessage("Error Fetching Weather Data.", 1);
        return;

  }
    loadingClear();
    temperature = response["current"]["temperature_2m"].get<float>();
    temperature_unit = response["current_units"]["temperature_2m"].get<string>();

    windspeed = response["current"]["wind_speed_10m"].get<float>();
    windspeed_unit = response["current_units"]["wind_speed_10m"].get<string>();

    winddirection = response["current"]["wind_direction_10m"].get<float>();
    winddirection_unit = response["current_units"]["wind_direction_10m"].get<string>();

    datetime = response["current"]["time"].get<string>();
    date = datetime.substr(0, 10);

    weather_code = response["current"]["weather_code"].get<int>();
    weather = getWeatherInfo();

    fetched = true;
}

void Weather::displayWeather(){
    if(!fetched){
        throw runtime_error("Weather not fetched");
    }
    cout<<"\033[1;m  Date: \033[0m"<<date<<endl;
    cout<<"\033[1;m  Temperature: \033[0m"<<temperature<<temperature_unit<<endl;
    cout<<"\033[1;m  Weather: \033[0m"<<weather<<endl;
    cout<<"\033[1;m  Wind Speed: \033[0m"<<windspeed<<windspeed_unit<<endl;
    cout<<"\033[1;m  Wind Direction: \033[0m"<<winddirection<<winddirection_unit<<endl;
}

string Weather::getWeatherInfo() {
        int code = this->weather_code;
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
