#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <string>
#include <QString>

#include "repositories/computerrepository.h"
#include "repositories/scientistrepository.h"
#include "models/computer.h"
#include "models/scientist.h"

class Service
{
public:
        Service();

        /* @brief Gets sorted list of Computer/Scientist
         * @return returns sorted vector of Computer/Scientist */
        vector<Scientist> getSortedScientistList();
        vector<Computer> getSortedComputerList();

        /* @brief searches table for matching string
         * @param searchString string to search for
         * @return retuns vector of object where searchsrting was found */
        vector<Scientist> searchScientists(QString searchString);
        vector<Computer> searchComputers(QString searchString);

        /* @brief Get list(vector) of scientist that have relation to param
         * @parameter finding relation to this object
         * @return returns list of associated Computer/scienteist */
        vector<Scientist> getAssociatedScientist(Computer computerDetails);
        vector<Computer> getAssociatedComputers(Scientist scientistDetails);

        /* @brief formats data to insert to DB
         * @return True if sucsessfully added and false if writing to database failed */
        bool createScientistToAdd(string name, string gender, int yearborn, int yeardied, string knownFor);
        bool createComputerToAdd(string name, string type, bool built, int yearBuilt);

        /* @brief finds TableId of scientist/computer to be removed
         * @parameter number list is at which container scientist/comp to remove is
         * @return True if sucsessfully "removed" and false if writing to database failed */
        bool removeScientist(int idScientistToRemove);
        bool removeComputer(int idComputerToRemove);

        /* @brief Creates relation between scientist and computer
         * @parameters Computer and scientist to add relation to
         * @return True if sucsessfully added and false if writing to database failed */
        bool createRelation(Computer relationComp, Scientist relationScientist);
        /* @brief Removes relation between scientist and computer
         * @parameters PK ID for computer and scientist to remove relation from
         * @return True if sucsessfully added and false if writing to database failed */
        bool removeRelation(int idScientist, int idComputer);
private:
        Computerrepository computerRepository;
        Scientistrepository scientistRepository;

};

#endif // SERVICE_H
