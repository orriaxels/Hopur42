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
        //Retrives a list of vector type and sorts. 
        //sortBy=1 sort by first name, 2 sort by last name, 3 sort by gender
        //4 sort by year born, 5 if sort by last name
        //Order of sort = 0 for Acending. 1 for decending

//        void createPerson(string name, char gender, int yborn, int ydied);
        void createPerson(string name, char gender, int yborn, int ydied, string quote);

//		void remove();  //ef timi gefst
//      void editEntery(); ef timi gefst

        //errorcheck functions
        bool isActionLegal(char choice);
        bool isNameLegal(string& name, string& illegal);
        bool isGenderLegal(char gender);
        bool isBirthYearLegal(int birth);
        bool isDeathYearLegal(int death, int birthYear);
        bool isQuoteLegal(string quote);

    private:
        string makeSearchable(vector<Persons> list, int index);
        
    	

};

#endif // SERVICE_H
