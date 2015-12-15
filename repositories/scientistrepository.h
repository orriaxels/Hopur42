#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H
#include <vector>
#include <QString>
#include <QtSql>

#include "models/scientist.h"

class Scientistrepository
{
public:
        Scientistrepository();

        /* @brief Adds user created scientist to database
         * @param newScientist is the object to add to database
         * @return returns true if sucsessfully added to database, false if not */
        bool addToDatabase(Scientist newScientist);

        /* @brief update scientist that is already in databse
         * @param scientist to be changed
         * @return returns true if sucsessfully added to database, false if not */
		    bool updateScientist(Scientist scientistUpdate);

        /* @brief Sets deleted flag for scientist as 1. Sets all relation as deleted as well
         * @param idToRemove of scientist to flag as deleted
         * @return returns true if database was sucsessfully updated, false if not */
        bool removeScientist(int idToRemove);

        /* @brief Querys scientists table for string
         * @param searchString is ready to put after LIKE statement in query
         * @return retuns vector of scientists where searchString was found */
        vector<Scientist> searchScientist(QString searchString);
		vector<Scientist> advancedSearchScientist(QString searchString);

        /* @brief Gets scientists not flagged deleted from database
         * @return retuns vector of Scientists*/
        vector<Scientist> getScientistList();

        /* @brief Finds all associated Scientists for id of computer
         * @param findForComputer to find associated cunterpart
         * @return retuns vector of scientists that are associated with parameter */
        vector<Scientist> getAssociatedScientists(int idOfComputerToMatch);
private:
        vector<Scientist> scientistsList;

		/* @brief used by member funcitons to get results after query is made
		 * @param resautls from query
		 * @return retuns resault of the query */
		vector<Scientist> queryScientistTable(QSqlQuery query);

		/* @brief used after deleting a record from database.
         *  Deletes any relation from junciton table
		 * @param idScientistToRemove id of scientist to remove from junciton table
		 * @return retuns vector of scientists that are associated with parameter */
        bool removeRelationScientist(int idScientistToRemove);
};

#endif // SCIENTISTREPOSITORY_H
