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

    string name, illegal;
    string knownFor;
    Service serVar;
    char gender;
    int bYear = 0;
    int dYear = 0;
    bool deathLoop = 0;
    
    cout << "Enter information" << endl;
    
    do{
        cout << "Name: "; 
        getline(cin, name);
        if(serVar.isNameLegal(name, illegal) == false){
           cout << "'" << illegal << "' "<< "not valid in name" << endl;
        }
    }while( !(serVar.isNameLegal(name, illegal)) );

    do{    
        cout << "Gender (f=female, m=male): ";
        cin >> gender;
        gender = tolower(gender);
        if(serVar.isGenderLegal(gender) == false){
            cout << "Invalid input, please reenter" << endl;
        }
    }while(!(serVar.isGenderLegal(gender)));    

    do{    
        cout << "Year of birth: ";
        cin >> bYear;
        if(cin.fail()){
            cin.clear();
            cin.get();   
           }
        if(serVar.isBirthYearLegal(bYear) == false){
             cout << "Invalid input, please reenter" << endl;
        }
    }while(!(serVar.isBirthYearLegal(bYear)));    


   do{    
        cout << "Year of death (\"0\" to skip): ";
        cin >> dYear;
        
        if(cin.fail()){
            cin.clear();
            cin.get();
            cout << "Invalid input, please insert a valid year" << endl;
            deathLoop = 1;
        }else{
            if(serVar.isDeathYearLegal(dYear, bYear)){
                deathLoop = 0;        
            }else{
                if(dYear < bYear){
                    cout << "Impossible, you can't be dead before you are born!" << endl;
                    deathLoop = 1;
                }
                else if(dYear == bYear){
                    cout << "Not likely, you are a not an important person in the computer world at the age 0" << endl;
                    deathLoop = 1;
                }        
            }
                
        }             
    }while(deathLoop);    
    
    do{
        cout << "Is known for (\"0\" to skip): ";
        cin.ignore();
        getline(cin, knownFor);
    }while(!(serVar.isKnownForLegal(knownFor)));


    serVar.createPerson(name, gender, bYear, dYear, knownFor);

    cout<<endl<<"Entry sucsessfully added to database"<<endl;
    
    system("pause");
    system("cls");
    
    runInterFace();
}

void InterFace::printDisplayMenu(){
    Service servVar;
    int sortWith, order;

    cout << "What would you like to sort by?" << endl
         << "1. First name" << "  ||  "
         << "2. Last name" << "  ||  "
         << "3. Gender" << "  ||  "
         << "4. Year of birth" << "  ||  "
         << "5. Year of death" << endl
         << "Enter choice (1-5): ";

    do{
        cin >> sortWith;
        cout << endl;  

        if(cin.fail()){
            cin.clear();
            cin.get();
            cout << "Invalid input. Please try again." << endl;
        }
        else if (sortWith > 5 || sortWith < 1){
            cout << "Invalid input. Please try again." << endl;
        }
   }while(sortWith > 5 || sortWith < 1);

    do{
        if(sortWith ==3){
            cout << "1. Males first" << "  ||  "
                 << "2. Females first" << endl <<"Enter choice: ";
            cin >> order;
        }
        else{
            cout << "1. Ascending(a-z)" << "  ||  "
                 << "2. Descending(z-a)" << endl << "Enter choice: ";
            cin >> order;
        }

        

        if (order == 1){
            servVar.sortDisplay(sortWith, 0);
            }
        else if (order == 2){
             servVar.sortDisplay(sortWith, 1);
            }
            
    }while (order != 1 && order !=2);

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