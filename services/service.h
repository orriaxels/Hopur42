#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <string>

#include "models/scientist.h"
#include "models/computer.h"
#include "repo/repository.h"



class Service
{
	public:
		Service();
		/*@brief Gets sorted list of Computer/Scientist
		* @param sortBy says what column to sort by
		* @param orderOfSort sort Acsending or Descending
		* @return returns sorted vector of Computer/Scientist */
		vector<Scientist> getSortedScientistList(int sortBy, bool orderOfSort);
		vector<Computer> getSortedComputerList(int sortBy, bool orderOfSort);

		/*@brief searches table for matching string
		* @param searchString string to search for
		* @return retuns vector of object where searchsrting was found */
		vector<Scientist> searchScient(string searchString);
		vector<Computer> searchComp(string searchString);

		/*@brief Get list(vector) of scientist that have relation to param
		* @parameter finding relation to this object
		* @return returns list of associated Computer/scienteist */
		vector<Scientist> getAssociatedScient(Computer compDetails);
		vector<Computer> getAssociatedComp(Scientist scienDetails);

		/*@brief formats data to insert to DB
		* @parameters self explanatory.
		* @return True if sucsessfully added and false if writing to database failed */
		bool createScientist(string name, string gender, int yborn, int ydied, string knownFor);
		bool createComputer(string compName, string compType, bool built, int yBuilt);

		/*@brief Creates relation between scientist and computer
		* @parameters Computer and scientist to add relation to
		* @return True if sucsessfully added and false if writing to database failed */
		bool createRelation(Computer relationComp, Scientist relationScientist);

		/*@brief finds TableId of scientist/computer to be "removed"
		* @parameter number list is at which container scientist/comp to remove is
		* @parameter listToRemoveFrom, contains the list the entery to remove was selected
		* @return True if sucsessfully "removed" and false if writing to database failed */
		bool removeScientEntery(int numberList, const vector<Scientist> listToRemoveFrom);
		bool removeCompEntery(int numberList, const vector<Computer> listToRemoveFrom);

		/*@brief Removes relation between scientist and computer
		* @parameters PK ID for computer and scientist to remove relation from
		* @return True if sucsessfully added and false if writing to database failed */
		bool removeRelation(int idScientist, int idComputer);
  private:
			Repository repository;

};

#endif // SERVICE_H
