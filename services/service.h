#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <string>

#include "models/persons.h"
#include "models/computers.h"
#include "repo/repository.h"



class Service
{
	public:
		Service();
		/*@brief Gets sorted list of computers/persons
		* @param sortBy says what column to sort by
		* @param orderOfSort sort Acsending or Descending
		* @return returns sorted vector of computers/persons */
		vector<Persons> getSortedPersonsList(int sortBy, bool orderOfSort);
		vector<Computers> getSortedComputersList(int sortBy, bool orderOfSort);

		/*@brief searches table for matching string
		* @param searchString string to search for
		* @return retuns vector of object where searchsrting was found */
		vector<Persons> searchScient(string searchString);
		vector<Computers> searchComp(string searchString);

		vector<Persons> getAssociatedPers(Computers compDetails);
		vector<Computers> getAssociatedComp(Persons persDetails);

		/*@brief Sorts data and makes ready to insert to DB
		* @parameters self explanatory.
		* @return True if sucsessfully added and false if writing to database failed */
		bool createPerson(string name, string gender, int yborn, int ydied, string knownFor);
		bool createComputer(string compName, string compType, bool built, int yBuilt);


		bool createRelation(Computers relationComp, Persons relationScientist);

		/*@brief finds TableId of person/computer to be "removed"
		* @parameter number list is at which container person/comp to remove is
		* @parameter listToRemoveFrom, contains the list the entery to remove was selected
		* @return True if sucsessfully "removed" and false if writing to database failed */
		bool removePersEntery(int numberList, const vector<Persons> listToRemoveFrom);
		bool removeCompEntery(int numberList, const vector<Computers> listToRemoveFrom);

		bool removeRelation(int idScientist, int idComputer);
  private:
			Repository repository;

};

#endif // SERVICE_H
