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
  * @param searchString2 assumes you are looking for first and last name
  * @return retuns vector of scientists/computers where searchString was found */
  vector<Persons> searchScientist(string searchString);
  vector<Persons> searchScientist(string searchString1, string searchString2);
  vector<Computers> searchComputer(string searchString);

  /*@brief Fetches sorted vector of all computers/scientists from database
  * @param byColumn what column to sort by
  * @param aceDesc  if sorted Ascending or Descending
  * @return retuns sorted vector of Scientists/computers*/
  vector<Persons> getScientistList(int byColumn, bool aceDesc);
  vector<Computers> getComputerList(int byColumn, bool aceDesc);

  /*@brief Gets Id of Associated computers/Scientists from junctiontable
  * @param findForComputer/findForPerson to find associated cunterpart
  * @return retuns vector with id of computers/scientists that are associated with parameter */
  vector<int> getAssociatedP(Computers findForComputer);
  vector<int> getAssociatedC(Persons findForPerson);
private:
  vector<Persons> scientistsList;
  vector<Computers> computerList;

};

#endif // REPOSITORY_H
