#include <string>
#include <vector>
#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

//Margin Functions
void margin();

//Loading Status Functions
void loading();
void loadingClear();

//Various Operations
std::string searchCity(std::string cityname, std::string countryname);
void getCords(std::string cityname, std::string countryname, std::vector<double> &cords);
void showWeather(double latitude, double longitude);
int weatherCode(int code);
#endif
