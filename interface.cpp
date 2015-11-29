#include <iostream>
#include "interface.h"
#include "service.h"

using namespace std;

InterFace::InterFace(){} //default constructor


void InterFace::runInterFace(){
    InterFace::displayMainMenu();
    InterFace::actionSelect();
}

int InterFace::actionSelect(){  
    char a = '0';
    do{
        cin >> a;
        switch(a){
            case '1':
                InterFace::printAddMenu();
                break;
            case '2':
                InterFace::printDisplayMenu();
                break;
            case '3':
                InterFace::printSearchMenu();
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

    //Hugsanlega haegt ad setja inn clearscreen her sidar
    //#include <stdlib.h>
    //system("cls"); //virkar bara fyrir windows samt

}

void InterFace::printAddMenu(){
    string name;
    Service var;
    cout << "Enter information" << endl;
    cout << "Name: " ;
    do{
        cin.ignore();
        getline(cin, name);
        if(!(var.isNameLegal(name))){
            cout << "Invalid input, reenter first name" << endl;
        }else{     
            }
           


    }while(!(var.isNameLegal(name)));
    cout << "Gender: ";
}

void InterFace::printDisplayMenu(){
    cout << "Display Menu" << endl;
    cout << "1. name:" << endl;
}

void InterFace::printSearchMenu(){
    cout << "Search Menu" << endl;
}

