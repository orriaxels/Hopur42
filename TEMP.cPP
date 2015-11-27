#include <iostream>
#include "persons.h"	//Eins og við vorum búin að hugsa þetta. 	
#include "interface.h" 	//Ekki klasi heldur header fyrir interface.cpp 
						//Interface er interaction milli tveggja aðila. Ss. input/output

using namespace std;

int main()
{
    do{
		interface.printMenu();
		switch(interface.getinput(){
			case '1': 	persons.addEntry();
						break;
			case '2': 	persons.search();
						break;
			case '3': 	persons.displayList();
						break;
			case '4': 	persons.deleteEntry();
						break;
			default:	return 0;		
		}
    }while(1); //eftir að útfæra break hér til að komast út úr falli. kemur seinna.

    return 0;
}