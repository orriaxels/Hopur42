#ifndef interface_h
#define interface_h

#include <iostream>
#include <string>
#include "persons.h"


using namespace std;


class InterFace //Ser um samdkipti vid notanda in/out
{
	public:
		InterFace();
		void runInterFace();
		void displayMainMenu();
		void printAddMenu();
		void printDisplayMenu();
		void printSearchMenu();
		int actionSelect();

	private:  // Verda liklega ekki breitur til ad vinna med
};

#endif