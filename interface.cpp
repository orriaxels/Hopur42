#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "interface.h"
#include "service.h"

using namespace std;

InterFace::InterFace(){} //default constructor


void InterFace::runInterFace(){
        InterFace::displayMainMenu();
        InterFace::actionSelect();    
}

int InterFace::actionSelect(){  
    char a;
    string dummyString; //lennti í smá veseni með getline, setti þetta inn samkvæmt
                        //internetinu, þetta virðist laga þá villu
    cout << "Please select an option from the list: ";
    cin >> a;
    bool loop;
    getline(cin, dummyString);

    if(a !='1' && a !='2' && a !='3' && a !='4' && a !='5'){
        cout << "Invalid input" << endl;
        
    }else{
        do{
            switch(a){
            case '1':
                cout << endl;
                InterFace::printAddMenu();
                break;
            case '2':
                cout << endl;
                InterFace::printDisplayMenu();
                break;
            case '3':
                cout << endl;
                InterFace::printSearchMenu();
                break;
            case '4':
                loop = 0;
                break;
            case '5':
                cout<<endl;
                InterFace::printRemoveMenu();
                break;
            default:
                cout << "Invalid" << endl;
                break;
        
            }
        }while(loop);
    }    
    return 0;
}

void InterFace::displayMainMenu(){
    cout<< "Welcome to this awesome database" << endl
        << endl
        << "What would you like to do?" << endl
        << "  1. Add a new entry" << endl
        << "  2. Display the database" << endl
        << "  3. Search the database" << endl
        << "  4. Quit" << endl
        << endl;
       

    //Hugsanlega haegt ad setja inn clearscreen her sidar
    //#include <stdlib.h>
    //system("cls"); //virkar bara fyrir windows samt
}

void InterFace::printAddMenu(){

    string name;
    string quote;
    Service serVar;
    char gender;
    int bYear = 0;
    int dYear = 0;
    bool deathLoop = 0;
    
    cout << "Enter information" << endl;
    
    do{
        cout << "Name: "; 
        getline(cin, name);
    }while( !(serVar.isNameLegal(name)) );
    do{    
        cout << "Gender (m for male / f for female): ";
        cin >> gender;
        gender = tolower(gender);
    }while(!(serVar.isGenderLegal(gender)));    



    do{    
        cout << "Year of birth: ";
        cin >> bYear;
       if(cin.fail()){
            cin.clear();
            cin.get();   
           }
    }while(!(serVar.isBirthYearLegal(bYear)));    


   do{    
        cout << "Year of death (input 0 if still alive): ";
        cin >> dYear;
        
        if(cin.fail()){
            cin.clear();
            cin.get();
            cout << "Invalid input, please insert valid year" << endl;
            deathLoop = 1;
        }else{
            if(serVar.isDeathYearLegal(dYear, bYear)){
                deathLoop = 0;        
            }else{
                deathLoop = 1;
            }        
        }     
    }while(deathLoop);    
    
    do{
        cout << "Enter famous quote (input 0 for no quote): ";
        cin.ignore();
        getline(cin, quote);
    }while(!(serVar.isQuoteLegal(quote)));

    serVar.createPerson(name, gender, bYear, dYear);

//   runInterFace(); //keyrir aftur main menu

}

void InterFace::printDisplayMenu(){
    Service servVar;
    int sortWith, order;

    cout << "What would you like to sort by?" << endl
         << "1. First name" << endl
         << "2. Last name" << endl
         << "3. Gender" << endl
         << "4. Year of birth" << endl
         << "5. Year of death" << endl;

    do{
        cin >> sortWith;
        cout << endl;  

        if(cin.fail()){
            cin.clear();
            cin.get();
            cout << "Invalid input. Please try again." << endl;
        }
        else if (sortWith > 5 || sortWith <1){
            cout << "Invalid input. Please try again." << endl;
        }
   }while(sortWith > 5 || sortWith < 1);

    do{
        if(sortWith ==3){
            cout << "1. Females first" << endl;
            cout << "2. Males first" << endl;
            cin >> order;
        }
        else{
            cout << "1. Ascending" << endl; //Sér fyrir gender?
            cout << "2. Descending" << endl;
            cin >> order;
        }

        

        if (order == 1){
            servVar.sortDisplay(sortWith, 0);
            }
        else if (order == 2){
             servVar.sortDisplay(sortWith, 1);
            }
            
    }while (order != 1 && order !=2);
}

void InterFace::printSearchMenu(){
    Service servVar;
    string searchS;

    cout << "What would you like to search for? " ;
    getline(cin, searchS);
    cout<<endl<<"Found \"" << searchS << "\" in following enteries:"<<endl<<endl;

    servVar.search(searchS);
}


void InterFace::printPerson(vector<Persons> &list){
    string buffer;

    cout<<"#  Name:   \t\t\t\tGender:\tBorn:\tDied:"<<endl; //\tQuote

    for(unsigned int i=0; i<list.size(); i++){
        cout << i+1;
        if(i<10)
            cout<<"  ";
        else if(9<i && i<100)
            cout<<" ";

        cout << list.at(i).getF() << " " << list.at(i).getL();

        buffer= list.at(i).getF() + " " + list.at(i).getL();
        for(unsigned int j=0; j< (37- buffer.length()); j++){
            cout<<" ";
        }

        if(list.at(i).getGender()){
            cout << "Female"<< '\t';}
        else{
            cout << "Male"<< '\t';}

        cout << list.at(i).getYearBorn() << '\t';

        if( 0 == (list.at(i).getYearDied()) )
            cout <<"Alive!" <<endl;
        else
            cout << list.at(i).getYearDied() <<endl;

        //cout << "Quote: " << list.at(i).getQuote() << endl;
    }
}

void InterFace::printRemoveMenu(){
    Service serVar;
    int enteryRemove, totalEnt;
    totalEnt= serVar.getListDatabase();
    cout<< "Which one of these enteries do you want to remove(select #)? ";


    do{    
        cin >> enteryRemove;

        if(cin.fail()){
            cin.clear();
            cin.get();
            cout<<"Invalid input. Enter number of entery from the list: ";   
           }
    }while( (cin.fail())  );

    serVar.removeEntery(enteryRemove);
}