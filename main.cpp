#include <iostream>
#include <limits>
#include <vector>

//Including Operations Header File
#include "operations.hpp"

using namespace std;

int main(){
	cout<<endl;
	cout<<"#========================== Weather APP ==========================#"<<endl;
	cout<<endl;;
	bool running = true;
	string cityname;
	string countryname;
	char choice;
	while(running){
		cout<<"  Enter the name of city: ";
		getline(cin, cityname);
		cout<<"  Enter the name of country: ";
		getline(cin, countryname);
		margin();
		loading();
		string location = searchCity(cityname, countryname);
		loadingClear();
		if(location != ""){
			vector<double> cords;
			cout<<"  Location Info: "<<location<<endl;
			margin();
			loading();
			getCords(cityname, countryname, cords);
			loadingClear();
			if(cords.size() >= 2 ){
			double latitude = cords[0];
			double longitude = cords[1];
			cout<<"  Latitude: "<<latitude<<endl;
			cout<<"  Longitude: "<<longitude<<endl;
			margin();
			loading();
			showWeather(latitude, longitude);
			}
		}
		margin();
		cout<<"  Do you want to search again (y/n): ";
		cin>>choice;
		while(true){
			if(choice == 'y' || choice == 'Y'){
			break;
			}
			else if(choice == 'n' || choice == 'N'){
			running = false;
			break;
			}
			else{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout<<"  Invalid Input. Please Try Aagain. "<<endl;
				cout<<"  Do you want to search again (y/n): ";
				cin>>choice;
            }
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		margin();
	}
	return 0;

}
