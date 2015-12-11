#ifndef scientist_h
#define scientist_h

#include <vector>
#include <string>

using namespace std;

class Scientist
{
	public:
		//Constructors
		Scientist();
    Scientist(string fName, string lName, bool pGender, int born, int died, string KnownFor);
		Scientist(int tableId, string fName, string lName, bool pGender, int born, int died, string KnownFor);

    //Returns value of variables.
		int getId() const;
    string getF() const;
		string getL() const;
    string getKnownFor() const;
    bool getGender() const;
    int getYearBorn() const;
    int getYearDied() const;

	private:
		int persId;					// PK id from database
		string firstName; 	// First name, if person has middle name it stores it here;
		string lastName;		// Last name
		string knownFor;		// If qoute is recorded for scientist
		bool gender; 				// False for male, true for female
		int yearBorn; 			// Year born
		int yearDied;				// Year of death, 0 if still alive
};

#endif // PERSONS_H
