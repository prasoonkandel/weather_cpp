#include <string>
#include <vector>
#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

//Margin Functions
void margin();

//Various Operations
std::vector<int> getCords(std::string cityname, std::string countryname);
std::string searchCity(std::string cityname, std::string countryname);
std::vector<std::string> showWeather(int latitude, int longitude);
void displayOutput(std::vector<std::string> &data);

#endif