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
//Margin Functions
void margin();

//Loading Status Functions
void loading();
void loadingClear();

//Various Operations
void showWeather(double latitude, double longitude);
std::string weatherCode(int code);
#endif
