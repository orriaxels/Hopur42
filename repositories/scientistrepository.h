#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H
#include <vector>
#include <QString>

#include "models/scientist.h"

class Scientistrepository
{
public:
        Scientistrepository();

        /* @brief Adds user created scientist to database
         * @param newScientist is the object to add to database
         * @return returns true if sucsessfully added to database, false if not */
        bool addToDatabase(Scientist newScientist);

        /* @brief Sets deleted flag for scientist as 1. Sets all relation as deleted as well
         * @param idToRemove of scientist to flag as deleted
         * @return returns true if database was sucsessfully updated, false if not */
        bool removeScientist(int idToRemove);

        /* @brief Querys all dataabase for string
         * @param searchString is ready to put after LIKE statement in query
         * @return retuns vector of scientists where searchString was found */
        vector<Scientist> searchScientist(QString searchString);

        /* @brief Gets scientists not flagged deleted from database
         * @return retuns vector of Scientists*/
        vector<Scientist> getScientistList();

        /* @brief Finds all associated Scientists for id of computer
         * @param findForComputer to find associated cunterpart
         * @return retuns vector of scientists that are associated with parameter */
        vector<Scientist> getAssociatedScientists(int idOfComputerToMatch);

        /* @brief Adds/removes relation between scientist and computers in database
         * @param idScientists is the PK of scientist to add relation findForComputer
         * @param idPkComputer vector of id's of computers to add(vector if case more than one)
         * @return returns true if sucsessfully added to database, false if not */
        bool addRelation(int idScientist, int idComputer);
        bool removeRelation(int idScientist, int idComputer);
private:
        vector<Scientist> scientistsList;
        bool removeRelationScientist(int idScientistToRemove);
};

#endif // SCIENTISTREPOSITORY_H
