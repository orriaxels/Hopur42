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
		Persons(string fName, string lName, int born, int died);
        Persons(string fName, string lName, int born, int died, string Quote);

        //Returns value of variables.
        string getF(); 
		string getL();
        string getQuote();
        bool getGender();
        int getYearBorn();
        int getYearDied();

        //Sets single variable of Person object
		void setFirst(const string firstName);
		void setLast(const string lastName);
		void setQuote(const string persQuote);
		void setGender(const bool persGender);
		void setBorn(const int yBorn);
		void setDied(const int yDied);        
	private:
		string firstname; 
		string lastname;
		string quote;
		bool gender; 	//False for male, true for female
		int yearBorn; 	
		int yearDied;
};

#endif // PERSONS_H
