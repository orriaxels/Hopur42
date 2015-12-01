#ifndef interface_h
#define interface_h

#include <iostream>
#include <string>
#include <vector>
#include "persons.h"


using namespace std;


class InterFace //Ser um samdkipti vid notanda in/out
{
	public:
		InterFace();
		void runInterFace();
		void printPerson(vector<Persons> &list);
		
    private:
    	void displayMainMenu();
		void printAddMenu();
		void printDisplayMenu();
		void printSearchMenu();
        int actionSelect(); 
        void printRemoveMenu();
};

#endif


