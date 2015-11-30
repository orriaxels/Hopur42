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

      
        void search(const string searchString); //Not tested
        bool isActionLegal(char choice);
        bool isNameLegal(string name);
        bool isGenderLegal(char gender);
        bool isBirthYearLegal(int birth);
        bool isDeathYearLegal(int death);
        bool isQuoteLegal(string quote);
        void sortDisplay(int sortBy); // Working
        //Retrives a list of vector type and sorts. 
        //sortBy=1 if sort by First name
        //sortBy=2 if sort by last name
        //sortBy=3 if sort by year born
        //sorbBy=4 if sort by last name
        //void search(const string searchString); 
        //Leitar i staki ad 


//		void remove();  //ef timi gefst
//      void editEntery(); ef timi gefst

    private:
    	//Takes vector of Persons and creates a single string to search for matcH  
        string makeSearchable(vector<Persons> list, int index);
        int birthYear;
        string n;
    	

};

#endif // SERVICE_H
