#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "services/service.h"
#include "ui/interface.h"
#include "models/persons.h"
#include "models/computers.h"
#include "repo/repository.h"
#include "util/objectsort.h"

using namespace std;

Service::Service(){//default constructor
}

void Service::search(string searchString){
    Repository repoVar;
    InterFace interVar;
    string buffer;
    vector<Persons> list=repoVar.getScientistList();
    vector<Persons> foundIn;

    //converts search query to lowercase
    transform(searchString.begin(), searchString.end(), searchString.begin(), ::tolower);

    for(unsigned int i=0; i < list.size(); i++){
        buffer=makeSearchable(list, i);
        if (buffer.find(searchString) != string::npos) { //compares 1 object agains searchstring
            foundIn.push_back(list.at(i));                 //if found puts object in foundIn vector
        }
    }

    if(foundIn.size() == 0)
        interVar.notFound(false, searchString);
    else{
        interVar.notFound(true, searchString);
        interVar.printPerson(foundIn);
    }
}

string Service::makeSearchable(vector<Persons> list, int index){

    string searchable="";
    ostringstream stringstream;

    searchable=list.at(index).getF();
    searchable+=" " ;

    searchable+=list.at(index).getL();
    searchable+=" " ;

    searchable+=list.at(index).getKnownFor();
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

//Sorts list
vector<Persons> Service::getSortedPersonsList(int sortBy, bool orderofsort){
    vector<Persons> personsList=repository.getScientistList();

    sort(personsList.begin(), personsList.end(), ObjectSort(sortBy, orderofsort));

    return personsList;
}

vector<Computers> Service::getSortedComputersList(int sortBy, bool orderofsort){
    vector<Computers> compList=repository.getComputerList();

    sort(compList.begin(), compList.end(), ObjectSort(sortBy, orderofsort));

    return compList;
}

void Service::createPerson(string name, string gender, int yborn, int ydied, string knownFor){


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
    if(gender == "f" || gender == "F")
        newP.setGender(true);
    else
        newP.setGender(false);

    //Sets birth and died year;
    newP.setBorn(yborn);
    newP.setDied(ydied);

    newP.setKnownFor(knownFor);

    repoVar.addToDatabase(newP);  //write new entery to the file
}


int Service::getListDatabase(){  //returns list from file
    Repository repoVar;
    InterFace intVar;
    vector<Persons> List=repoVar.getScientistList();

    intVar.printPerson(List);

    return List.size();
}

// void Service::removeEntery(int enteryRemove){
//     Repository repoVar;
//     vector<Persons> List=repoVar.getScientistList();
//
//     //Backs up current list into file backup_itpersons.txt
//   //  repoVar.backupList(List);
//
//     //removes selcted from list
//     List.erase(List.begin() + (enteryRemove-1) );
//
//     //Rewrites the hole list to orginal file
//     repoVar.rewriteList(List);
// }

bool Service::somthingthere(){
    Repository repoVar;
    vector<Persons> listForsize=repoVar.getScientistList();

    if(listForsize.size()==0)
        return false;
    else
        return true;
}

bool Service::isNameLegal(string& name, string& illegal){
    if(name.empty()){
        cout << "Invalid input, reenter" << endl;
        return false;
    }else{
        for(unsigned int i = 0; i < name.length(); ++i){ //sets first letter in name as upper case
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
