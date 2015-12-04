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
		//Starts main interface of the program
		
		void printPerson(vector<Persons> &list); 
		//Prints out a list of person objects
		
		void notFound(bool wasfound, const string searchStr); 
		//Display messages depending on if searchStr was found
		//wasfound=true prints found message and vice versa
		
    private:
    	void displayMainMenu(); 
    	void printAddMenu();
		void printAddPersonMenu();
		void printAddCompMenu();
		void printDisplayMenu();
		void printSearchMenu();
        void actionSelect(); 
        void printRemoveMenu();
};

#endif


