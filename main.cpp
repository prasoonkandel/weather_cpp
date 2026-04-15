#include <iostream>
#include <limits>

//Including Operations Header File
#include "operations.hpp"

using namespace std;

int main(){
	cout<<endl;
	cout<<"#===========================Weather APP===========================#"<<endl;
	cout<<endl;
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
		string location = searchCity(cityname, countryname);
		
		if(location != ""){
			cout<<"  Location Info: "<<location<<endl;
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
