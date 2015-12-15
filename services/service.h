#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <string>
#include <QString>

#include "repositories/computerrepository.h"
#include "repositories/scientistrepository.h"
#include "repositories/relationrepository.h"
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

        /* @brief Get list(vector) of Computer/Scientist that have relation to param
         * @parameter finding relation Computer/Scientist
         * @return returns list of associated Computer/scienteist */
        vector<Scientist> getAssociatedScientist(Computer computerDetails);
        vector<Computer> getAssociatedComputers(Scientist scientistDetails);

        /* @brief formats data to and sends to database
         * @return true if sucsessfully added and false if writing to database failed */
        bool createScientistToAdd(string name, string gender, int yearborn, int yeardied, string knownFor);
        bool createComputerToAdd(string name, string type, bool built, int yearBuilt);

		/* @brief Sends modified entery to database to update
		 * @parameter contains the modified scientist or computer to uptdate
         * @return true if sucsessfully added and false if writing to database failed */
        bool updateScientist(Scientist scientistUpdate);
        bool updateComputer(Computer computerUpdate);

        /* @brief removes scientist/computer from database
         * @parameter PK id in database table
         * @return true if sucsessfully "removed" and false if writing to database failed */
        bool removeScientist(int idScientistToRemove);
        bool removeComputer(int idComputerToRemove);

        /* @brief Creates relation between scientist and computer
         * @parameters Computer and scientist to add relation to
         * @return true if sucsessfully added and false if writing to database failed */
        bool createRelation(int idScientist, int idComputer);

        /* @brief Removes relation between scientist and computer
         * @parameters PK ID for computer and scientist to remove relation from
         * @return true if sucsessfully added and false if writing to database failed */
        bool removeRelation(int idScientist, int idComputer);

        /* @brief finds total number of records in junction database
         * @return true if sucsessfully added and false if writing to database failed */
		int numberOfRelations();
private:
        // @brief private variables to use when calling repositories
        Computerrepository computerRepository;
        Scientistrepository scientistRepository;
        Relationrepository relationRepository;

        /* @brief finds sepirates first name and last name from string and
         * @parameter firstName contains full name(unsepirated)
         * @parameters lastName is empty string that
         * @return first last name sepirated in parameters */
		void seperateFirstLast(string &firstName, string &lastName);


};

#endif // SERVICE_H
