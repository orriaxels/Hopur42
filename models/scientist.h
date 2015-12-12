#ifndef scientist_h
#define scientist_h
#include <string>

using namespace std;

class Scientist
{
public:
        //Available constructors
        Scientist();
        Scientist(string fName, string lName, bool pGender, int born, int died, string KnownFor);
        Scientist(int tableId, string fName, string lName, bool pGender, int born, int died, string KnownFor);

        //Returns value of the private variables.
        int getId() const;
        string getF() const;
        string getL() const;
        string getKnownFor() const;
        bool getGender() const;
        int getYearBorn() const;
        int getYearDied() const;

private:
        int scientistId;       // Primary key id from database
        string firstName;      // First name, if person has middle name it stores it here;
        string lastName;       // Last name
        string knownFor;       // What is scientist is best known for
        bool gender;           // False for male, true for female
        int yearBorn;          // Year born
        int yearDied;          // Year of death, 0 if still alive
};

#endif // PERSONS_H
