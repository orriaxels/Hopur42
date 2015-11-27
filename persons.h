#ifndef persons_h
#define persons_h

#include <iostream>
#include <string>

using namespace std;




class Persons   
{ 
	public:
		Persons(); //A ekki ad turfa fleiri foll en constuctors. 
		Persons(string fName, string lName, int born, int died);
        Persons(string fName, string lName, int born, int died, string Quote);

	private:
		string firstname; //Getur verid got til ad flokka eftir first/last
		string lastname;
		string quote;
		int yearBorn;  //Hugsanlega setja upp breyta sidar med dagsetningu ef timi gefst
		int yearDied;
};

#endif // PERSONS_H
