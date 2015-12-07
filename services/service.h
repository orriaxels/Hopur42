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

		bool createPerson(string name, string gender, int yborn, int ydied, string knownFor);
		bool createComputer(string compName, string compType, bool built, int yBuilt);

		bool removeEntery(int numberList, const vector<Persons> listToRemoveFrom);
		bool removeEntery(int numberList, const vector<Computers> listToRemoveFrom);

		void search(string searchString);
		int getListDatabase();
		bool somthingthere();
		bool isNameLegal(string& name, string& illegal);

  private:
			Repository repository;
      string makeSearchable(vector<Persons> list, int index);




};

#endif // SERVICE_H
