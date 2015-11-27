#include <iostream>
#include "persons.h"

using namespace std;

void printMenu();
bool choice();

int main()
{
  //  do
    printMenu();
//    function print menu
//    getuserselection
//    while();

    choice();


    return 0;
}

void printMenu()
{

    cout << " Welcome to this awesome database" << endl;
    cout << endl;
    cout << " What would you like to do?" << endl;
    //cout << endl;
    cout << "  1. Add a new entry" << endl;
    cout << "  2. Display the database" << endl;
    cout << "  3. Search the database" << endl;
    cout << "  4. Quit" << endl;
    cout << endl;
    cout << "Please select an option from the list: ";

}

bool choice()
{
    char num='0';


    do{
        cin >> num;

        switch(num){
            case '1':
                //addPerson();
                cout << "add" << endl;
                break;
            case '2':
                //display();
                cout << "display" << endl;
                break;
            case '3':
                //search();
                cout << "search" << endl;
                break;
            case '4':
                cout << "false" << endl;
                return false;
            default:
                cout << "Input not available" << endl;
                break;
        }
          } while(num !='1' && num !='2' && num !='3' && num !='4');

    return 0;
}

/*

    function getUserSelection with error check
    switch
        function Search
        Fucntion display
        Funciton add
        **function delete
        */


//Test

