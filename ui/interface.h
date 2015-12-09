#ifndef interface_h
#define interface_h

#include <string>
#include <vector>

#include "ui/interface.h"
#include "services/service.h"
#include "models/computer.h"
#include "models/scientist.h"
#include "utilities/inputcheck.h"

class InterFace
{
	public:
		InterFace();
		void runInterFace();  //Starts main interface
		void invalidInput();	//Prints out error message
  private:
		Service serviceVar;
		Inputcheck inputCheckVar;

		void displayMainMenu();	// Display main menu options
		void actionSelect();		// Gets user input to what function user wants to use

		void searchMenu();			//Displays interface for search function

		//Prints out vector of scientist/computers in list form
		void printScientist(vector<Scientist> scienList);
		void printComputers(vector<Computer> compList);


		void addMenu();
		void addScientistMenu();
		void addCompMenu();
		void addRelations();

		void displayMenu();
		void dispScientistMenu();
		void dispCompMenu();

		void removeMenu();
		void removeScienMenu();
		void removeCompMenu();
		void removeRelation();

		//display details about selected entry in database
		void displayDetails(Computer compDetails);
		void displayDetails(Scientist scienDetails);

};

#endif
