#ifndef interface_h
#define interface_h

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
		void runInterFace();
		void invalidInput();
  private:
		Service serviceVar;
		Inputcheck inputCheckVar;


		void displayMainMenu();	// Display main menu options
		void actionSelect();		// Gets user input to what function user wants to use

		void searchMenu();			//Displays interface for search function

		//Prints out vector of persons/computers in list form
		void printPerson(vector<Persons> persList);
		void printComputers(vector<Computers> compList);


		void printAddMenu();
		void printAddPersonMenu();
		void printAddCompMenu();

		void printDisplayMenu();
		void printDispPersMenu();
		void printDispCompMenu();

		void printRemoveMenu();
		void printRemovePersMenu();
		void printRemoveCompMenu();

		void displayDetails(Computers compDetails);
		void displayDetails(Persons persDetails);

};

#endif
