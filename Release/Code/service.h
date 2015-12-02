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

        void search(string searchString); 
        //search for entery that contains a string
        
        void sortDisplay(int sortBy, bool orderofsort);
        //sortBy=1 sort by first name, 2 sort by last name, 3 sort by gender
        //       4 sort by year born,  5 if sort by last name
        //Order of sort = 0 for Acending. 1 for decending

        
        void createPerson(string name, string gender, int yborn, int ydied, string knownFor);
        //used to create new entry. 

        
		int getListDatabase();  
        void removeEntery(int enteryRemove);
        //used when deleting a entry from DB

       
        bool somthingthere();
         //Checks if DB is emty

        bool isNameLegal(string& name, string& illegal);
        //errorcheck functions
        
    private:
        string makeSearchable(vector<Persons> list, int index);
        //takes elements of Person vector and converts into lowercase string for comparing
        
    	

};

#endif // SERVICE_H
