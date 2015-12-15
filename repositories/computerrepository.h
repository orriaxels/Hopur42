#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H
#include <vector>
#include <QString>
#include <QtSql>

#include "models/computer.h"

class Computerrepository
{
public:
        Computerrepository();

        /* @brief Adds user created computer to database
         * @param newScientist is the object to add to database
         * @return returns true if sucsessfully added to database, false if not */
        bool addToDatabase(Computer newComputer);

        /* @brief updates computer that is already in databse
         * @param computer to be changed
         * @return returns true if sucsessfully added to database, false if not */
		bool updateComputer(Computer computerUpdate);

        /* @brief Sets deleted flag for scientist as 1. Sets all relation as deleted as well
         * @param idToRemove of scientist to flag as deleted
         * @return returns true if database was sucsessfully updated, false if not */
        bool removeComputer(int idToRemove);

        /*@brief searches database for matching string column by column
         * @param searchString string to search for in database
         * @return retuns vector of computer where searchString was found */
        vector<Computer> searchComputer(QString searchString);
		vector<Computer> advancedSearchComputer(QString searchString);

        /* @brief Gets computers not flagged deleted from database
         * @return retuns vector of computers*/
        vector<Computer> getComputerList();

        /* @brief Gets Id of Associated Computer/Scientists from junctiontable
         * @param findForComputer/findForScientist to find associated cunterpart
         * @return retuns vector Computer/scientists that are associated with parameter */
        vector<Computer> getAssociatedComputers(int idOfScientistToMatch);

private:
        vector<Computer> computerList;

        /* @brief used by member funcitons to get results after query is made
         * @param resautls from query
         * @return retuns resault of the query */
		vector<Computer> queryComputerTable(QSqlQuery query);

        /* @brief used after deleting a record from database.
         *  Deletes any relation from junciton table
		 * @param idScientistToRemove id of scientist to remove from junciton table
		 * @return retuns vector of scientists that are associated with parameter */
        bool removeRelationComputers(int idComputerToRemove);
};

#endif // COMPUTERREPOSITORY_H
