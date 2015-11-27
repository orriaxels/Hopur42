

#include <iostream>
#include <string>

using namespace std;
#include "persons.h"
#include "interface.h"

InterFace::InterFace();
		
		InterFace::displayMainMenu();	
		InterFace::nums();	


void InterFace::displayMainMenu(){
	cout << "Welcome to this awesome database" << endl;
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << "  1. Add a new entry" << endl;
    cout << "  2. Display the database" << endl;
    cout << "  3. Search the database" << endl;
    cout << "  4. Quit" << endl;
    cout << endl;
    cout << "Please select an option from the list: ";
}

int InterFace::nums(){
	char a = '0';
	do{
		cin >> a;
        switch(a){
            case '1':
                InterFace::addName();
                break;
            case '2':
                InterFace::printDisplayMenu();
                break;
            case '3':
                //search();
                cout << "search" << endl;
                break;
            case '4':
                cout << "false" << endl;
                return 0;
            default:
                cout << "Input not available" << endl;
                break;
        }
    }while(a !='1' && a !='2' && a !='3' && a !='4');

    	return 0;
}

void InterFace::printDisplayMenu(){
	cout << "Display Menu" << endl;
	cout << "1. name:" << endl;

}