#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <string>

#include "models/persons.h"
#include "models/computers.h"
#include "repo/repository.h"

using namespace std;

class Service
{
	public:
		Service();

		vector<Persons> getSortedPersonsList(int sortBy, bool orderOfSort);
		vector<Computers> getSortedComputersList(int sortBy, bool orderOfSort);

		vector<Persons> searchScient(string searchString);
		vector<Computers> searchComp(string searchString);

		bool createPerson(string name, string gender, int yborn, int ydied, string knownFor);
		bool createComputer(string compName, string compType, bool built, int yBuilt);

		bool removePersEntery(int numberList, const vector<Persons> listToRemoveFrom);
		bool removeCompEntery(int numberList, const vector<Computers> listToRemoveFrom);

		int getListDatabase();
		bool somthingthere();

  private:
			Repository repository;

};

#endif // SERVICE_H
