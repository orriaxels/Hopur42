#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H
#include <vector>
#include <QString>

#include "models/scientist.h"
#include "models/computer.h"


class Scientistrepository
{
public:
    Scientistrepository();

    /*@brief Adds user created scientist/computer to database
    * @param newScientist/newComp comp/scientist to add
    * @return returns true if sucsessfully added to database, false if not */
    bool addToDatabase(Scientist newScientist);

    /*@brief Adds user created relation betwenn scientist/computer to database
    * @param pk of both comp/scien to add relation
    * @return returns true if sucsessfully added to database, false if not */
    bool addRelation(int idPkComputer, int idPkScientists);

    /*@brief Sets deleted flag in database as 1. Does not remove completly from DB
    * @param idToRemove of scientist/comp to flag as deleted
    * @return returns true if database was sucsessfully updated, false if not */
    bool removeScientist(int idToRemove);
    bool removeRelation(int idScientist, int idComputer);

    /*@brief searches database for matching string column by column
    * @param searchString string to search for in database
    * @param searchString2 assumes you are looking for first and last name
    * @return retuns vector of scientists/Computer where searchString was found */
    vector<Scientist> searchScientist(QString searchString);

    /*@brief Fetches sorted vector of all Computer/scientists from database
    * @param byColumn what column to sort by
    * @param aceDesc  if sorted Ascending or Descending
    * @return retuns sorted vector of Scientists/Computer*/
    vector<Scientist> getScientistList(int byColumn, bool aceDesc);

    /*@brief Gets Id of Associated Computer/Scientists from junctiontable
    * @param findForComputer/findForScientist to find associated cunterpart
    * @return retuns vector Computer/scientists that are associated with parameter */
    vector<Computer> getAssociatedC(Scientist findForScientist);

  private:
    vector<Scientist> scientistsList;



};

#endif // SCIENTISTREPOSITORY_H
