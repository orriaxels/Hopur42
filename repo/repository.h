#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "models/persons.h"
//#include "computer.h"

class Repository  //Eina blokkin sem hefur bein samskipti vid .txt
{
public:
  Repository();
  bool addToDatabase(Persons newPerson);
  //bool addToDatabase(Computer newComp);   Need class name!!

  vector<Persons> getScientistList();
  //vector<Computer> getComputerList();
  //vector<Junction> getJunctionList();

private:
  vector<Persons> scientistsList;	//contains list of all Persons in file

};

#endif // REPOSITORY_H
