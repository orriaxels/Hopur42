#ifndef SERVICE_H
#define SERVICE_H
#include <iostream>
#include <vector>
#include <string>

#include "interface.h"
#include "persons.h"
#include "repository.h"

using namespace std;

class Service  //Ser um allar adgeridr, sort, search, kannski meira
{
	public:
		Service();

        void search(const string searchString); 
        //search for entery that contains a string
        
        void sortDisplay(int sortBy, bool orderofsort);
        //sortBy=1 sort by first name, 2 sort by last name, 3 sort by gender
        //       4 sort by year born,  5 if sort by last name
        //Order of sort = 0 for Acending. 1 for decending


        //used for createing new entry
        void createPerson(string name, char gender, int yborn, int ydied);
        void createPerson(string name, char gender, int yborn, int ydied, string knownFor);

        //used when deleting a entry from DB
		int getListDatabase();  
        void removeEntery(int enteryRemove);

        //errorcheck functions
        bool isActionLegal(char choice);
        bool isNameLegal(string& name);
        bool isGenderLegal(char gender);
        bool isBirthYearLegal(int birth);
        bool isDeathYearLegal(int death, int birthYear);
        bool isKnownForLegal(string knownFor);

    private:
        string makeSearchable(vector<Persons> list, int index);
        
    	

};

#endif // SERVICE_H
