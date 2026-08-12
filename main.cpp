#include <iostream>
#include <limits>

//Including Operations Header File
#include "operations.hpp"

using namespace std;

int main(){
	bool running = true;
	string query;
	char choice;
	while(running){
	clearScreen();
	cout<<"\033[36m#==========================\033[1;36m Weather CPP \033[36m==========================#\033[0m"<<endl;
	cout<<endl;;
		cout<<"  Enter the full location: ";
		getline(cin, query);
		margin();
		loading();
		Location l1(query);
		l1.searchLocation();
		loadingClear();
		if(l1.getDisplayName() != ""){

			cout<<"  Location Info: "<<l1.getDisplayName()<<endl;
			margin();
			Weather w1(l1);
			loading();
			w1.fetchWeather();
			w1.displayWeather();

		}
		margin();
		cout<<"  Do you want to search again (y/n): ";
		cin>>choice;
		while(true){
			if(choice == 'y' || choice == 'Y'){
			clearScreen();
			break;
			}
			else if(choice == 'n' || choice == 'N'){
			margin();
            cout<<"  Thanks for using weather_cpp. Developer's Info: https://prasoonkandel.com \n";
			running = false;
			break;
			}
			else{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				errorMessage("Invalid Input. Please Try Aagain.", 1);
				cout<<"  Do you want to search again (y/n): ";
				cin>>choice;
            }
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return 0;

}
