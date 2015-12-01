#ifndef persons_h
#define persons_h

#include <iostream>
#include <string>

using namespace std;




class Persons   
{ 
	public:
		//Constructors
		Persons(); 
		Persons(string fName, string lName, bool pGender, int born, int died);
        Persons(string fName, string lName, bool pGender, int born, int died, string KnownFor);

        //Returns value of variables.
        string getF(); 
		string getL();
        string getKnownFor();
        bool getGender();
        int getYearBorn();
        int getYearDied();

        //Sets single variable of Person object
		void setFirst(const string firstName);
		void setLast(const string lastName);
		void setKnownFor(const string persknownFor);
		void setGender(const bool persGender);
		void setBorn(const int yBorn);
		void setDied(const int yDied);        
	private:
		string firstname; 	//First name, if person has middle name it stores it here;
		string lastname;	//Last name 
		string knownfor;		//If qoute is recorded for person
		bool gender; 		//False for male, true for female
		int yearBorn; 		//Year born
		int yearDied;		//Year of death, 0 if still alive
};

#endif // PERSONS_H
