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

void Service::search(string searchString){
    Repository repoVar;
    InterFace interVar;
    string buffer;
    vector<Persons> list=repoVar.getList();
    vector<Persons> foundIn;

    //converts search query to lowercase
    transform(searchString.begin(), searchString.end(), searchString.begin(), ::tolower);

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

    //convert to lowercase to match serachstring
    transform(searchable.begin(), searchable.end(), searchable.begin(), ::tolower);

    return searchable;
}


//Used to compare values of Person for sorting algorithm
bool compFirstname(Persons p1, Persons p2){
    return p1.getF() < p2.getF(); }
bool compLastname(Persons p1, Persons p2){
    return p1.getL() < p2.getL(); }
bool compGender(Persons p1, Persons p2){
    return p1.getGender() < p2.getGender(); }
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
        case 3: // Sort by gender
            sort(list.begin(), list.end(), compGender);
            break;    
        case 4: //Sort by year born
            sort(list.begin(), list.end(), compYearBorn);
            break;
        case 5: //Sort by year died
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


void Service::createPerson(string name, char gender, int yborn, int ydied){
    string buffer="";
    vector<string> nameContainer;
    stringstream nameStream;
    nameStream.str(name);
    Persons newP;
    Repository repoVar;
    
    //Seperate name string and set first and last name    
    while (nameStream >> buffer){ //seperates the string word by word using stringstream
            if(buffer=="-1")
                break;
            nameContainer.push_back(buffer);
    }
    //Creates string containing all the name but the last name(last element in vector)
    buffer="";
    for(unsigned int i=0; i<nameContainer.size()-1; i++){
        buffer+=nameContainer.at(i);

        if(i< (nameContainer.size()-2))
            buffer+=" ";
    }
    newP.setFirst(buffer);  //Sets first name
    buffer="";
    newP.setLast(nameContainer.back()); //sets last element in vector as last name
    //-------------

    //Sets gender to by input. False for male, true for female
    if(gender=='f')
        newP.setGender(true);
    else
        newP.setGender(false);

    //Sets birth and died year;
    newP.setBorn(yborn);
    newP.setDied(ydied); 

    repoVar.writeToFile(newP);

}

void Service::createPerson(string name, char gender, int yborn, int ydied, string knownFor){

    string buffer="";
    vector<string> nameContainer;
    stringstream nameStream;
    nameStream.str(name);
    Persons newP;
    Repository repoVar;
    
    //Seperate name string and set first and last name    
    while (nameStream >> buffer){ //seperates the string word by word using stringstream
            if(buffer=="-1")
                break;
            nameContainer.push_back(buffer);
    }
    //Creates string containing all the name but the last name(last element in vector)
    buffer="";
    for(unsigned int i=0; i<nameContainer.size()-1; i++){
        buffer+=nameContainer.at(i);

        if(i< (nameContainer.size()-2))
            buffer+=" ";

    }
    newP.setFirst(buffer);  //Sets first name
    buffer="";
    newP.setLast(nameContainer.back()); //sets last element in vector as last name
    //-------------

    //Sets gender to by input. False for male, true for female
    if(gender=='f')
        newP.setGender(true);
    else
        newP.setGender(false);

    //Sets birth and died year;
    newP.setBorn(yborn);
    newP.setDied(ydied);  

    newP.setKnownFor(knownFor);

    repoVar.writeToFile(newP);   
}


int Service::getListDatabase(){  //ef timi gefst
    Repository repoVar;
    InterFace intVar;
    vector<Persons> List=repoVar.getList();

    intVar.printPerson(List);

    return List.size();
}

void Service::removeEntery(int enteryRemove){
    Repository repoVar;
    vector<Persons> List=repoVar.getList();

    //Backs up current list into file backup_itpersons.txt
    repoVar.backupList(List);

    //removes selcted from list
    List.erase(List.begin() + (enteryRemove-1) );

    //Rewrites the hole list to orginal file
    repoVar.rewriteList(List);
}


bool Service::isNameLegal(string& name, string& illegal){
    if(name.empty()){
        cout << "Invalid input, reenter" << endl;
        return false;
    }else{
        for(unsigned int i = 0; i < name.length(); ++i){
            if((islower(name[0])) || (islower(name[i]) && name[i-1] == ' ')){
                name[i] = toupper(name[i]);
            }
            else if(!isalpha(name[i])){
                if(name[i] == ' ' && name[i+1] == ' '){
                    name.erase(name.begin()+i); 
                    i--; 
                }else if (name[i] != ' '){
                    illegal = name[i];
                    return false;   
                }
            }else if( (i != 0) && (isupper(name[i]) && name[i-1] != ' ')){
                name[i] = tolower(name[i]);
            }
        }
    } 
    
    return true;
}

bool Service::isGenderLegal(char gender){
    if(gender == 'm' || gender == 'f'){
        return true;    
    }else{
        return false;
    }
}

bool Service::isBirthYearLegal(int birth){
        if(birth > 1800 && birth < 2005){
            return true;
        }else{        
            return false;
        }
}

bool Service::isDeathYearLegal(int death, int birthYear){
            if( (death > birthYear && death < 2016) || (death == 0) ){
                return true;
            }else{
                return false;
            }                
}

bool Service::isKnownForLegal(string knownFor){
    if(knownFor == "0"){
        return true;
    }
    else if(knownFor.length() < 5){
        return false;
    }
    else{
        return true;
    }
}