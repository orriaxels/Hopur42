#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H

#include <vector>
#include "repositories/computerrepository.h"
#include "models/computer.h"

class Computerrepository
{
public:
    Computerrepository();

    /*@brief Adds user created scientist/computer to database
  * @param newScientist/newComp comp/scientist to add
  * @return returns true if sucsessfully added to database, false if not */
  bool addToDatabase(Computer newComp);

  /*@brief Adds user created relation betwenn scientist/computer to database
  * @param pk of both comp/scien to add relation
  * @return returns true if sucsessfully added to database, false if not */
  bool addRelation(int idPkComputer, int idPkScientists);

  /*@brief Sets deleted flag in database as 1. Does not remove completly from DB
  * @param idToRemove of scientist/comp to flag as deleted
  * @return returns true if database was sucsessfully updated, false if not */
  bool removeComputer(int idToRemove);
  bool removeRelation(int idScientist, int idComputer);

  /*@brief searches database for matching string column by column
  * @param searchString string to search for in database
  * @param searchString2 assumes you are looking for first and last name
  * @return retuns vector of scientists/Computer where searchString was found */
  vector<Computer> searchComputer(string searchString);

  /*@brief Fetches sorted vector of all Computer/scientists from database
  * @param byColumn what column to sort by
  * @param aceDesc  if sorted Ascending or Descending
  * @return retuns sorted vector of Scientists/Computer*/
  vector<Computer> getComputerList(int byColumn, bool aceDesc);

private:
  vector<Computer> computerList;
};

#endif // COMPUTERREPOSITORY_H
