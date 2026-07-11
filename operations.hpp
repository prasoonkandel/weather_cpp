#include <string>
#include <vector>
#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

// Location Class
class Location{
    private:
        double latitude;
        double longitude;
        std::string display_name;
        std::string query;
    public:
        Location(std::string query);
        double getLatitude();
        double getLongitude();
        std::string getDisplayName();
        void fetchCords();
        void searchLocation();
};

// Weather Class
class Weather{
    double latitude;
    double longitude;

    float temperature;
    std::string temperature_unit;

    float windspeed;
    std::string windspeed_unit;

    float winddirection;
    std::string winddirection_unit;

    std::string datetime;
    std::string date;

    int weather_code;
    std::string weather;

    std::string weatherDecoder(int code);

    public:
    void fetchWeather();
    void displayWeather();

};
//Margin Functions
void margin();

//Loading Status Functions
void loading();
void loadingClear();

//Various Operations
void showWeather(double latitude, double longitude);
std::string weatherCode(int code);
#endif
