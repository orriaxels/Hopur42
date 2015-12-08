#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "models/persons.h"
#include "models/computers.h"

class Repository
{
public:
  Repository();

  /*@brief Adds user created scientist/computer to database
  * @param newPerson/newComp comp/scientist to add
  * @return returns true if sucsessfully added to database, true if not */
  bool addToDatabase(Persons newPerson);
  bool addToDatabase(Computers newComp);

  /*@brief Sets deleted flag in database as 1. Does not remove completly from DB
  * @param enteryToRemoveId of scientist/comp to flag as deleted
  * @return returns true if database was sucsessfully updated, true if not */
  bool removePerson(int enteryToRemoveId);
  bool removeComputer(int enteryToRemoveId);

  /*@brief searches database for matching string column by column
  * @param searchString string to search for in database
  * @return retuns vector of scientists/computers where searchString was found */
  vector<Persons> searchScientist(string searchString);
  vector<Computers> searchComputer(string searchString);

  /*@brief Return vector of all computers/scientists from database sorted
  * @param byColumn what column to sort by
  * @param aceDesc  if sorted Ascending or Descending
  * @return retuns sorted vector of Scientists/computers*/
  vector<Persons> getScientistList(int byColumn, bool aceDesc);
  vector<Computers> getComputerList(int byColumn, bool aceDesc);
private:
  vector<Persons> scientistsList;
  vector<Computers> computerList;

};

#endif // REPOSITORY_H
