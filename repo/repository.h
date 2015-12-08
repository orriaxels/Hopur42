#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "models/persons.h"
#include "models/computers.h"

class Repository
{
public:
  Repository();

  bool addToDatabase(Persons newPerson);
  bool addToDatabase(Computers newComp);

  bool removePerson(int enteryToRemoveId);
  bool removeComputer(int enteryToRemoveId);

  vector<Persons> searchScientist(string searchString);
  vector<Computers> searchComputer(string searchString);

  vector<Persons> getScientistList(int byColumn, bool aceDesc);
  vector<Computers> getComputerList(int byColumn, bool aceDesc);

private:
  vector<Persons> scientistsList;	//contains list of all Persons in file
  vector<Computers> computerList;

};

#endif // REPOSITORY_H
