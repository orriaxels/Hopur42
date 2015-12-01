#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <limits>

#include "interface.h"
#include "service.h"

using namespace std;

InterFace::InterFace(){} //default constructor


void InterFace::runInterFace(){
        InterFace::displayMainMenu();
        InterFace::actionSelect();    
}

void InterFace::actionSelect(){  
    char a;
    string dummyString; //lennti í smá veseni með getline, setti þetta inn samkvæmt
    bool loop;                    //internetinu, þetta virðist laga þá villu

    do{
    cout << "Please select an option from the list: ";
    cin >> a;
    getline(cin, dummyString);

    if(a !='1' && a !='2' && a !='3' && a !='4' && a !='5')
        cout << "Invalid input" << endl;

    }while(a !='1' && a !='2' && a !='3' && a !='4' && a !='5');
        

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
            cout<<endl;
            InterFace::printRemoveMenu();
            break;
        case '5':
            loop = 0;
            break;
        default:
            cout << "Invalid" << endl;
            break;
    
        }
    }while(loop );
}

void InterFace::displayMainMenu(){
    cout<< "Welcome! This database contains information about great computer scientists." << endl
        << endl
        << "What would you like to do?" << endl
        << "  1. Add a new entry" << endl
        << "  2. Display the database" << endl
        << "  3. Search the database" << endl
        << "  4. Remove entry from database"<<endl
        << "  5. Quit" << endl
        << endl;
}

void InterFace::printAddMenu(){

    Service serVar;
    string name, illegal;
    string knownFor="";
    string gender="";
    int bYear = 0;
    int dYear = 0;

    cout << "Enter information" << endl;
   
    //Get name input
    do{
        cout << "Name: "; 
        getline(cin, name);
        if(serVar.isNameLegal(name, illegal) == false){
           cout << "'" << illegal << "' "<< "not valid in name" << endl;
        }
    }while( !(serVar.isNameLegal(name, illegal)) );

    //Get gender input
    do{
        cout << "Gender (f=female, m=male): ";
        cin >> gender;
        if(gender != "f" && gender != "F" && gender != "m" && gender != "M"){
            cin.clear();
            cin.ignore();
            cout<<"Invalid input."<<endl;
        }
    }while(gender != "f" && gender != "F" && gender != "m" && gender != "M");

    //Get birth year input
    do{
        cout << "Year of birth: ";
        cin >> bYear;
        if(cin.fail() || bYear < 1 || bYear > 2010 ){
            cin.clear();
            cin.ignore( 1000, '\n' ) ; 
            cout<<"Invalid input."<<endl;   
        }

    }while( bYear < 1 || bYear > 2010 );


    //Get death year input
    do{    
        cout << "Year of death (\"0\" if alive): ";
        cin >> dYear;
        
        if( cin.fail() || (dYear > 2015) ||  ( (dYear < bYear+8) && dYear != 0 )  ){//google says youngest CS is at least 10
            if  (dYear > 2015)
                cout<<"Invalid input. Litle pessimistic arent we?"<<endl;  
            else if ( (dYear < bYear+8) ) { 
                cout<<"Invalid input. Have to be at least 8."<<endl; }
            else {
                cout<<"Invalid input."<<endl;}

            cin.clear();
            cin.ignore( 1000, '\n' ) ;     
        }       
    }while( (dYear > 2015) || ( (dYear < bYear+8) && dYear != 0 ) );
    
    //Get input Known for info
    do{
        cout << "Is known for (\"0\" to skip): ";
        cin.ignore();
        getline(cin, knownFor);
        if((knownFor != "0") && (knownFor.length() < 3) )
            cout<<"Invalid input."<<endl;
    }while( (knownFor != "0") && (knownFor.length() < 3) );


    serVar.createPerson(name, gender, bYear, dYear, knownFor);

    cout<<endl<<"Entry sucsessfully added to database"<<endl;
    
    system("pause");
    system("cls");
    
    runInterFace();
}

void InterFace::printDisplayMenu(){
    Service servVar;
    int sortWith, order;

    if(servVar.somthingthere()){
        cout << "What would you like to sort by?" << endl
             << "1. First name" << "  ||  "
             << "2. Last name" << "  ||  "
             << "3. Gender" << "  ||  "
             << "4. Year of birth" << "  ||  "
             << "5. Year of death" << endl;

        do{
            cout << "Enter choice: ";
            cin >> sortWith;  

            if(cin.fail() || (sortWith !=1 && sortWith !=2 && sortWith !=3 && sortWith !=4 && sortWith !=5 )){
                cin.clear();
                cin.ignore( 1000, '\n' ) ; 
                cout << "Invalid input." << endl;
            }
       }while(sortWith !=1 && sortWith !=2 && sortWith !=3 && sortWith !=4 && sortWith !=5 );

        
        if(sortWith ==3 ){
            cout << "1. Males first" << "  ||  "
                 << "2. Females first" << endl;
        }
        else{
            cout << "1. Ascending(a-z)" << "  ||  "
                 << "2. Descending(z-a)" << endl;
        }           

        do{
            cout << "Enter choice: ";
            cin >> order;  

            if( cin.fail() || (sortWith !=1 && sortWith !=2) ){
                cin.clear();
                cin.ignore( 1000, '\n' ) ; 
                cout << "Invalid input." << endl;
            }
        }while( order != 1 && order !=2);

        if (order == 1){
            servVar.sortDisplay(sortWith, 0);
        }
        else if (order == 2){
             servVar.sortDisplay(sortWith, 1);
        }
    }
    else{
        cout<<"Nothing to display(database is empty)";
    }

    cout<<endl<<endl;

    system("pause");
    system("cls");
    
    runInterFace();
}

void InterFace::printSearchMenu(){
    Service servVar;
    string searchS;

    cout << "What would you like to search for? " ;
    getline(cin, searchS);

    

    servVar.search(searchS);

    cout<<endl;
    system("pause");
    system("cls");
    
    runInterFace();
}

void InterFace::notFound(bool wasfound, const string searchStr){
    if(wasfound)
        cout<<endl<<"Found \"" << searchStr << "\" in following enteries:"<<endl;
    else
        cout<<"No enteries conatining \"" << searchStr << "\" found in database."<<endl;

}


void InterFace::printPerson(vector<Persons> &list){
    string buffer;

    if( list.size() == 0)
        cout<<endl<<"Nothing to display"<<endl;
    else{
        cout<<endl<<"#  Name:   \t\t\t\tGender:\tBorn:\tDied:\tKnown for:"<<endl; //

        for(unsigned int i=0; i<list.size(); i++){
            cout << i+1;
            if(i<9)
                cout<<"  ";
            else if(8<i && i<99)
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
                cout <<"Alive" <<'\t';
            else
                cout << list.at(i).getYearDied() << '\t' ;


            if( "0 " == (list.at(i).getKnownFor()) )
                cout << " " <<endl;
            else
                cout << list.at(i).getKnownFor() << endl;
        }
    }
}

void InterFace::printRemoveMenu(){
    Service serVar;
    int enteryRemove;
    serVar.getListDatabase();
    cout<< endl << "Which one of these enteries do you want to remove(select #)? ";


    do{    
        cin >> enteryRemove;

        if(cin.fail()){
            cin.clear();
            cin.get();
            cout<<"Invalid input. Enter number of entery from the list: ";   
           }
    }while( (cin.fail())  );

    serVar.removeEntery(enteryRemove);
    cout<< endl<<"Entery sucsessfully removed. (backup_itPersons.txt contains orginal list)"<<endl; 

    system("pause");
    system("cls");
    
    runInterFace();
}