#include "interface.h"

Interface::Interface()
{

}
/* hægt að útfæra þessi föll þá hér og láta þau interface við Persons.h
 * Látum koma í ljós hvort við viljum nota fleiri klasa eftir það.
void printMenu()
{
    cout << " Welcome to this awesome database" << endl;
    cout << endl;
    cout << " What would you like to do?" << endl;
    cout << "  1. Add a new entry" << endl;
    cout << "  2. Display the database" << endl;
    cout << "  3. Search the database" << endl;
    cout << "  4. Quit" << endl;
    cout << endl;
    cout << "Please select an option from the list: ";
}

void choice(){
    char num='0';
    do{
        cin >> num;

        switch(num){
            case '1':
                addPerson();
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
                return 0;
            default:
                cout << "Input not available" << endl;
                break;
        }
          } while(num !='1' && num !='2' && num !='3' && num !='4');

    return 0;
}

void addPerson(){
    string name,sex;
        int birthYear, deathYear;
        char agree;

        do{
            cout << "Full name: ";
            cin.ignore();
            getline (cin, name);
            cout << "Gender (m/f): ";
            getline (cin, sex);
            cout << "Year of birth: ";
            cin >> birthYear;
            cout << "Year of death: ";
            cin >> deathYear;

            cout << "Input another person (y/n): ";
            cin >> agree;

        }while(agree == 'y' | agree == 'Y');

}
*/
