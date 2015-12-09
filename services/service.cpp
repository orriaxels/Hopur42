#include <vector>
#include <string>
#include <sstream>

#include "services/service.h"
#include "ui/interface.h"
#include "models/scientist.h"
#include "models/computer.h"
#include "repo/repository.h"


Service::Service(){}//default constructor

vector<Scientist> Service::searchScient(string searchString){

  //To seperate string for diffrent querys
  string buffer="";
  vector<string> substringContainer;
	stringstream searchStream;
	searchStream.str(searchString);
	while (searchStream >> buffer){
      //To fit into like query prend/append % on both sides of searchstring
      buffer.insert (0, 1, '%');
      buffer+='%';

			substringContainer.push_back(buffer);
	}

  if(substringContainer.size() == 1){
    vector<Scientist> foundIn=repository.searchScientist( substringContainer.at(0) );
    return foundIn;
  }
  else{
    vector<Scientist> foundIn=repository.searchScientist(substringContainer.at(0), substringContainer.at(1));
    return foundIn;
  }

}

vector<Computer>Service::searchComp(string searchString){
  //To fit into query prend/append % on both sides of searchstring
  searchString.insert (0, 1, '%');
  searchString+='%';

  vector<Computer> foundIn=repository.searchComputer(searchString);
  return foundIn;
}


vector<Scientist> Service::getSortedScientistList(int sortBy, bool orderOfSort){
    vector<Scientist> ScientistList=repository.getScientistList(sortBy, orderOfSort);
    return ScientistList;
}

vector<Computer> Service::getSortedComputerList(int sortBy, bool orderOfSort){
    vector<Computer> compList=repository.getComputerList(sortBy, orderOfSort);
    return compList;
}


vector<Scientist> Service::getAssociatedScient(Computer compDetails){
  vector<Scientist> assScientists=repository.getAssociatedP(compDetails);
  return assScientists;
}

vector<Computer> Service::getAssociatedComp(Scientist scienDetails){
  vector<Computer> assComputer=repository.getAssociatedC(scienDetails);
  return assComputer;
}


bool Service::createScientist(string name, string gender, int yborn, int ydied, string knownFor){
    string buffer="", bufferFirst="", bufferLast="";
    bool bufferGender;
    vector<string> nameContainer;

    //To be able to seperate first and last name a sstream is created
    stringstream nameStream;
    nameStream.str(name);
    while (nameStream >> buffer){
          nameContainer.push_back(buffer);
    }

    if(nameContainer.size() == 1){//in case only one name is entered sets as first rather than lastname
      bufferFirst= nameContainer.back();
    }
    else{
      for(unsigned int i=0; i<nameContainer.size()-1; i++){ //first name arae all but the last in string
          bufferFirst+=nameContainer.at(i);
          if(i < (nameContainer.size()-2))
              bufferFirst+=" ";
      }
      bufferLast= nameContainer.back(); //sets last element in vector as last name
    }

    if(gender == "f" || gender == "F")
        bufferGender=true;
    else
        bufferGender=false;

    Scientist newScientist(bufferFirst, bufferLast, bufferGender, yborn, ydied, knownFor);

    if( repository.addToDatabase(newScientist) )
      return true;
    else
      return false;

}

bool Service::createComputer(string compName, string compType, bool built, int yBuilt){
  Computer newComputer(compName, compType, built, yBuilt);
  if( repository.addToDatabase(newComputer) )
    return true;
  else
    return false;
}

bool Service::createRelation(Computer relationComp, Scientist relationScientist){
  int idComputer=relationComp.getId(),
      idScientist=relationScientist.getId();
  if( repository.addRelation(idComputer, idScientist) )
    return true;
  else
    return false;
}



bool Service::removeScientEntery(int numberList, const vector<Scientist> listToRemoveFrom){
  int idOfScientist = ( listToRemoveFrom.at(numberList) ).getId();
  if( repository.removeScientist(idOfScientist) )
    return true;
  else
    return false;
}

bool Service::removeCompEntery(int numberList, const vector<Computer> listToRemoveFrom){
  int idOfComp = ( listToRemoveFrom.at(numberList) ).getId();
  if( repository.removeComputer(idOfComp) )
    return true;
  else
    return false;
}

bool Service::removeRelation(int idScientist, int idComputer){
  if( repository.removeRelation(idScientist, idComputer))
    return true;
  else
    return false;
}
