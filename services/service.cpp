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

vector<Persons> Service::searchScient(string searchString){
  vector<Persons> foundIn=repository.searchScientist(searchString);
  return foundIn;
}
vector<Computers>Service::searchComp(string searchString){
  vector<Computers> foundIn=repository.searchComputer(searchString);
  return foundIn;
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
        if(i < (nameContainer.size()-2))
            bufferFirst+=" ";
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

bool Service::removePersEntery(int numberList, const vector<Persons> listToRemoveFrom){
  int idOfPerson = ( listToRemoveFrom.at(numberList) ).getId();
  if( repository.removePerson(idOfPerson) )
    return true;
  else
    return false;
}

bool Service::removeCompEntery(int numberList, const vector<Computers> listToRemoveFrom){
  int idOfComp = ( listToRemoveFrom.at(numberList) ).getId();
  if( repository.removeComputer(idOfComp) )
    return true;
  else
    return false;
}
