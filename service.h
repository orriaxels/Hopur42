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
        void sortDisplay(int sortBy);   //Working
        void search(const string searchString); //Not tested
//		void remove();  //ef timi gefst
//      void editEntery(); ef timi gefst

    private:
    	//Takes vector of Persons and creates a single string to search for matcH  
        string makeSearchable(vector<Persons> list, int index);
    	

};

#endif // SERVICE_H
