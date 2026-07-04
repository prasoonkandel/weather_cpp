#include <iostream>
#include <limits>
#include <vector>

//Including Operations Header File
#include "operations.hpp"

using namespace std;

int main(){
	cout<<endl;
	cout<<"\033[36m#==========================\033[1;36m Weather APP \033[36m==========================#\033[0m"<<endl;
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
		string query = cityname + "," + countryname;
		Location l1(query);
		l1.searchLocation();
		loadingClear();
		if(l1.getDisplayName() != ""){

			cout<<"  Location Info: "<<location<<endl;
			margin();
			l1.fetchCords();
			double latitude = l1.getLatitude();
			double longitude = l1.getLongitude();
			loading();
			showWeather(latitude, longitude);

		}
		margin();
		cout<<"  Do you want to search again (y/n): ";
		cin>>choice;
		while(true){
			if(choice == 'y' || choice == 'Y'){
			margin();
			break;
			}
			else if(choice == 'n' || choice == 'N'){
			margin();
            cout<<"\033[36m  Thanks for using weather_cpp. Developer's Info: https://prasoonkandel.com \033[0m\n";
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
	}
	return 0;

}
