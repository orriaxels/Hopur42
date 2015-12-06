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

		void search(string searchString);

		vector<Persons> getSortedPersonsList(int sortBy, bool orderofsort);
		vector<Computers> getSortedComputersList(int sortBy, bool orderofsort);

		void createPerson(string name, string gender, int yborn, int ydied, string knownFor);
		int getListDatabase();
		void removeEntery(int enteryRemove);
		bool somthingthere();
		bool isNameLegal(string& name, string& illegal);

  private:
			Repository repository;
      string makeSearchable(vector<Persons> list, int index);




};

#endif // SERVICE_H
