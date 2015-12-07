#ifndef interface_h
#define interface_h

#include <iostream>
#include <string>
#include <vector>

#include "ui/interface.h"
#include "services/service.h"
#include "models/computers.h"
#include "models/persons.h"
#include "util/inputcheck.h"

class InterFace
{
	public:
		InterFace();
		void runInterFace(); 		//Starts main interface of the program
		void notFound(bool wasfound, const string searchStr); 		//Display messages depending on if searchStr was found  wasfound=true prints found message and vice versa
		void invalidInput();
  private:
		Service serviceVar;
		void printComputers(vector<Computers> compList);
		void printPerson(vector<Persons> persList); 		//Prints out a list of person objects
		void displayMainMenu();
		void printAddMenu();
		void printAddPersonMenu();
		Inputcheck inputCheckVar;
		void printAddCompMenu();
		void printDisplayMenu();
		void printDispPersMenu();
		void printDispCompMenu();
		void printSearchMenu();
		void printPersSearchMenu();
		void printCompSearchMenu();
		void actionSelect();
		void printRemoveMenu();
		void printRemovePersMenu();
		void printRemoveCompMenu();


};

#endif
