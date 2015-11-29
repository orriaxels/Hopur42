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
    string name, quote;
    Service var;
    char gender;
    int bYear = 0;
    int dYear = 0;
    bool loop = 0;
    
    cout << "Enter information" << endl;
    
    do{
        cout << "Name: " ;
        cin.ignore();
        getline(cin, name);
        if(!(var.isNameLegal(name))){
            cout << "Invalid input, please reenter" << endl;
        }
    }while(!(var.isNameLegal(name)));
    
    do{    
        cout << "Gender (m for male / f for female): ";
        cin >> gender;
        gender = tolower(gender);
        if(!(var.isGenderLegal(gender))){
            cout << "Invalid input, please reenter" << endl;
        }
    }while(!(var.isGenderLegal(gender)));    


    do{    
        cout << "Year of birth: ";
        cin >> bYear;
        if(!(var.isBirthYearLegal(bYear))){
           if(cin.fail()){
                bYear = 0;
                cin.clear();
                cin.get();
                cout << "Invalid input, please insert valid year " << endl;     
           }else{
                cout << "Invalid input, please insert valid year " << endl; 
            }    
        }
    }while(!(var.isBirthYearLegal(bYear)));    

   do{    
        cout << "Year of death (input 0 if still alive): ";
        cin >> dYear;
        if(cin.fail()){
            cin.clear();
            cin.get();
            cout << "Invalid input, please insert valid year " << endl;
            loop = 1;
        }else{
            if(var.isDeathYearLegal(dYear)){
                loop = 0;        
            }else{
                loop = 1;
            }        
        }
         
    }while(loop);    
    
    do{
        cout << "Enter famous quote (input 0 for no quote): ";
        cin.ignore();
        getline(cin, quote);
        if(!(var.isQuoteLegal(quote))){
            cout << "Ivalid amount characters, needs at least 6" << endl;
        }
   }while(!(var.isQuoteLegal(quote)));


}

void InterFace::printDisplayMenu(){
    cout << "Display Menu" << endl;
    cout << "1. name:" << endl;
}

void InterFace::printSearchMenu(){
    cout << "Search Menu" << endl;
}

// <<<<<<< HEAD
// void InterFace::printPerson(vector<Persons> list){

//     for(unsigned int i=0; i<list.size(); i++){
//         cout << "Name: " << list.at(i).getF() << " " list.at(i).getL() << endl;
//         cout << "Gender: "
//              if(at(i).getGender() == false){
//                 cout << "Male";}
//              else{
//                 cout << "Female";}
//         cout << "Year born: " << list.at(i).getYearBorn() << endl;
//         cout << "Died: " << list.at(i).getYearDied() << endl;
//         //cout << "Quote: " << list.at(i).getQuote() << endl;
//     }
// }

// =======
// >>>>>>> origin/master
