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
		void displayMainMenu();
		void printAddMenu();
		void printDisplayMenu();
		void printSearchMenu();
        int actionSelect(); //Af hverju skilar tetta fall int? Virdist ekki notad
        void printPerson(vector<Persons> &list);

    private:
    			// Verda liklega ekki breitur til ad vinna med
                // Hugsanlega haegt ad setja hjalparfoll
};

#endif
