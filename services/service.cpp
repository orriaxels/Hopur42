#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "services/service.h"
#include "ui/interface.h"
#include "models/persons.h"
#include "models/computers.h"
#include "repo/repository.h"


Service::Service(){//default constructor
}

void Service::search(string searchString){
    // Repository repoVar;
    // InterFace interVar;
    // string buffer;
    // //vector<Persons> list=repoVar.getScientistList();
    // //vector<Persons> foundIn;
    //
    // //converts search query to lowercase
    // transform(searchString.begin(), searchString.end(), searchString.begin(), ::tolower);
    //
    // for(unsigned int i=0; i < list.size(); i++){
    //     buffer=makeSearchable(list, i);
    //     if (buffer.find(searchString) != string::npos) { //compares 1 object agains searchstring
    //         foundIn.push_back(list.at(i));                 //if found puts object in foundIn vector
    //     }
    // }
    //
    // if(foundIn.size() == 0)
    //     interVar.notFound(false, searchString);
    // else{
    //     interVar.notFound(true, searchString);
    //     interVar.printPerson(foundIn);
    // }
}

vector<Persons> Service::getSortedPersonsList(int sortBy, bool orderOfSort){

    vector<Persons> personsList=repository.getScientistList(sortBy, orderOfSort);
    return personsList;
}

vector<Computers> Service::getSortedComputersList(int sortBy, bool orderOfSort){

    vector<Computers> compList=repository.getComputerList(sortBy, orderOfSort);
    return compList;
}

bool Service::createPerson(string name, string gender, int yborn, int ydied, string knownFor){

    string buffer="", bufferFirst="", bufferLast="";
    bool bufferGender;
    vector<string> nameContainer;

    //To be able to seperate first and last name
    stringstream nameStream;
    nameStream.str(name);
    while (nameStream >> buffer){
          nameContainer.push_back(buffer);
    }

    for(unsigned int i=0; i<nameContainer.size()-1; i++){
        bufferFirst+=nameContainer.at(i);
        if(i< (nameContainer.size()-2))
            buffer+=" ";
    }
    bufferLast= nameContainer.back(); //sets last element in vector as last name


    if(gender == "f" || gender == "F")
        bufferGender=true;
    else
        bufferGender=false;

    Persons newPerson(bufferFirst, bufferLast, bufferGender, yborn, ydied, knownFor);
    if( repository.addToDatabase(newPerson) )
      return true;
    else
      return false;

}

bool Service::createComputer(string compName, string compType, bool built, int yBuilt){
  Computers newComputer(compName, compType, built, yBuilt);
  if( repository.addToDatabase(newComputer) )
    return true;
  else
    return false;

}

int Service::getListDatabase(){  //returns list from file
    Repository repoVar;
    InterFace intVar;
    //vector<Persons> List=repoVar.getScientistList();

    //intVar.printPerson(List);

    //return List.size();
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
    //vector<Persons> listForsize=repoVar.getScientistList();

    // if(listForsize.size()==0)
    //     return false;
    // else
    //     return true;
}
