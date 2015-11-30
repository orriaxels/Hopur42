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
        void printDisplayMenu(); //Spyr notenda hvernig hann vill persónurnar sorteraðar, sendir inn int og bool í sort fall.
        void printSearchMenu(); //Nær í streng frá notenda og sendir í search fall.
        void actionSelect(); //Notandi velur aðgerð og kallar á viðeigandi fall (Display, add etc.)
        void printPerson(vector<Persons> &list);

    private:
    			// Verda liklega ekki breitur til ad vinna med
                // Hugsanlega haegt ad setja hjalparfoll
};

#endif
