#include <string>
#include <vector>
#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

// Location Class
class Location{
    private:
        double latitude;
        double longitude;
        double display_name;
        std::string query;
    public:
        Location(std::string query);
        double getLatitude();
        double getLongitude();
        void fetchCords(std::string display_name);
        std::string searchLocation();
};
//Margin Functions
void margin();

//Loading Status Functions
void loading();
void loadingClear();

//Various Operations
std::string searchCity(std::string cityname, std::string countryname);
void getCords(std::string cityname, std::string countryname, std::vector<double> &cords);
void showWeather(double latitude, double longitude);
std::string weatherCode(int code);
#endif
