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

		void displayMainMenu();
		void actionSelect();

		void printPerson(vector<Persons> persList);
		void printComputers(vector<Computers> compList);


		void printAddMenu();
		void printAddPersonMenu();
		void printAddCompMenu();

		void printDisplayMenu();
		void printDispPersMenu();
		void printDispCompMenu();

		void searchMenu();
		void printPersSearchMenu();
		void printCompSearchMenu();


		void printRemoveMenu();
		void printRemovePersMenu();
		void printRemoveCompMenu();

};

#endif
