#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "service.h"
#include "interface.h"
#include "persons.h"
#include "repository.h"

using namespace std;

Service::Service(){//default constructor
}

void Service::search(const string searchString){
    Repository repoVar;
    InterFace interVar;
    string buffer;
    vector<Persons> list=repoVar.getList();
    vector<Persons> foundIn;

    for(unsigned int i=0; i < list.size(); i++){
        buffer=makeSearchable(list, i);
        if (buffer.find(searchString) != string::npos) {
            foundIn.push_back(list.at(i));
        }
    }
    interVar.printPerson(foundIn);
}

string Service::makeSearchable(vector<Persons> list, int index){

    string searchable="";
    ostringstream stringstream;

    searchable=list.at(index).getF();
    searchable+=" " ;		//svo ekki finnist stafir tar sem skett er saman

    searchable+=list.at(index).getL();
    searchable+=" " ;

    stringstream << list.at(index).getYearBorn();
    searchable+=stringstream.str();
    stringstream.str("");
    searchable+=" ";

    stringstream << list.at(index).getYearDied();
    searchable+=stringstream.str();

    return searchable;
}

// bool isActionLegal(char choice){
//     if(choice.length() > 1 && choice.length() < 1){
//         cout << "Invalid input"
//         return false;
//     }
//     else if(!isalnum(choice)){
//         cout << "Invalid input" << endl;
//         return false;
//     }
// }

bool Service::isNameLegal(string name){
   cout << name << endl;
   for(unsigned int i = 0; i < name.length(); ++i){
        if((islower(name[0])) || (islower(name[i]) && name[i-1] == ' ')){
            name[i] = toupper(name[i]);
        }else if(!isalpha(name[i])){
            if(name[i] == ' ' && name[i+1] == ' '){
                cout <<"test" << endl;
                name.erase(name.begin()+i); 
                i--; 
            }else if (name[i] != ' '){
                cout << "'" << name[i] << "' "<< "not valid in name" << endl;
                return false;   
            }
        }else if( (i != 0) && (isupper(name[i]) && name[i-1] != ' ')){
            name[i] = tolower(name[i]);
        }
    }
    //n = name;
    cout << n <<endl;
    return true;

}




    // if(name.length() < 2 || name.length() > 31){
    //     return false;
    // }    
    // else{
    //     return true;
    // }


bool Service::isGenderLegal(char gender){
    if(gender == 'm' || gender == 'f'){
        return true;    
    }else{
        return false;
    }
}

bool Service::isBirthYearLegal(int birth){
     birthYear= birth;
        if(birth > 1800 && birth < 2005){
            return true;
        }else{        
            return false;
        }
}

bool Service::isDeathYearLegal(int death){
            if( (death > birthYear && death < 2016) || (death == 0) ){
                return true;
            }else if(death == birthYear){
                cout << "Invalid input, can't be the same as year of birth" << endl;
                return false;
            }    
            else{
                cout << "Invalid input, valid input from 1800 - 2005" << endl;
                return false;
            }            
}

bool Service::isQuoteLegal(string quote){
    if(quote.length() == 0){
        return true;
    }
    else if(quote.length() < 5){
        return false;
    }
    else{
        return true;
    }
}



/*
void Service::remove()  ef timi gefst
{

}

void Service::editEntery()  //ef timi gefst
{

}
*/

//Used to compare values of Person for sorting algorithm
bool compFirstname(Persons p1, Persons p2){
    return p1.getF() < p2.getF(); }
bool compLastname(Persons p1, Persons p2){
    return p1.getL() < p2.getL(); }
bool compYearBorn(Persons p1, Persons p2){
    return p1.getYearBorn() < p2.getYearBorn(); }
bool compYearDied(Persons p1, Persons p2){
    return p1.getYearDied() < p2.getYearDied(); }


//Sorts list
void Service::sortDisplay(int sortBy, bool orderofsort){
    Repository repoVar;
    InterFace interVar;
    vector<Persons> list=repoVar.getList();

    switch(sortBy){
        case 1: //Sort by First name
            sort(list.begin(), list.end(), compFirstname);
            break;
        case 2: // Sort by last name
            sort(list.begin(), list.end(), compLastname);
            break;
        case 3: //Sort by year born
            sort(list.begin(), list.end(), compYearBorn);
            break;
        case 4: //Sort by year died
            sort(list.begin(), list.end(), compYearDied);
            break;
        default:
            break; //Shouldnt happen. Error check on input needed
    }
    if(orderofsort){
        reverse(list.begin(),list.end());
    }
    interVar.printPerson(list);
}