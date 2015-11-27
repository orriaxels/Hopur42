

#include <iostream>
#include <string>

using namespace std;
#include "persons.h"

#ifndef interface_h
#define interface_h

class InterFace:public Persons
{
	public:
		InterFace();
		void displayMainMenu();
		void printDisplayMenu();
		int nums();


	private:
		//char num;


};

#endif