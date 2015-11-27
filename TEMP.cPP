#include <iostream>
#include "persons.h"	//Eins og við vorum búin að hugsa þetta. 	
#include "interface.h" 	//Ekki klasi heldur header fyrir interface.cpp 
						Interface er interaction milli tveggja aðila. Ss. input/output

using namespace std;

int main()
{
    do{
		interface.printMenu();
		switch(interface.getinput();){
			case1 add
			case2 search
			case3 display
			case4 deleta
			default anything else quit		
		}
    }while(1); //eftir að útfæra break hér til að komast út úr falli. kemur seinna.

    return 0;
}

