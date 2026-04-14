#include <iostream>
#include <limits>
using namespace std;

void margin();

int main(){
	
	cout<<"#===========================Weather APP===========================#"<<endl;
	bool running = true;
	string cityname;
	char choice;
	while(running){
		cout<<"  Enter the name of city: ";
		getline(cin, cityname);
		margin();
		cout<<"  The name of the city is: "<<cityname<<endl;
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

void margin(){
	cout<<"==================================================================="<<endl;
}