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
		
		void printPerson(vector<Persons> persList);
		void printComputers(vector<Computers> compList);

		void displayMainMenu();
		void printAddMenu();
		void printAddPersonMenu();
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
