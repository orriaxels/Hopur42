#ifndef SERVICE_H
#define SERVICE_H
#include <iostream>
#include <vector>
#include <string>

#include "ui/interface.h"
#include "models/persons.h"
#include "repo/repository.h"

using namespace std;

class Service  //Ser um allar adgeridr, sort, search, kannski meira
{
	public:
		Service();

		void search(string searchString);
		//search for entery that contains a string

		vector<Persons> getSortedPersonsList(int sortBy, bool orderofsort);
		vector<Computers> getSortedComputersList(int sortBy, bool orderofsort);

		void createPerson(string name, string gender, int yborn, int ydied, string knownFor);
		//used to create new entry.


		int getListDatabase();
		void removeEntery(int enteryRemove);
		//used when deleting a entry from DB


		bool somthingthere();
		 //Checks if DB is emty

		bool isNameLegal(string& name, string& illegal);
		//errorcheck functions

  private:
			Repository repository;
      string makeSearchable(vector<Persons> list, int index);
      //takes elements of Person vector and converts into lowercase string for comparing



};

#endif // SERVICE_H
