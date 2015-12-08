#ifndef persons_h
#define persons_h

#include <vector>
#include <string>

using namespace std;

class Persons
{
	public:
		//Constructors
		Persons();
    Persons(string fName, string lName, bool pGender, int born, int died, string KnownFor);
		Persons(int tableId, string fName, string lName, bool pGender, int born, int died, string KnownFor);

    //Returns value of variables.
		int getId() const;
    string getF() const;
		string getL() const;
    string getKnownFor() const;
    bool getGender() const;
    int getYearBorn() const;
    int getYearDied() const;

	private:
		int persId;
		string firstname; 	//First name, if person has middle name it stores it here;
		string lastname;	//Last name
		string knownfor;	//If qoute is recorded for person
		bool gender; 		//False for male, true for female
		int yearBorn; 		//Year born
		int yearDied;		//Year of death, 0 if still alive
};

#endif // PERSONS_H
