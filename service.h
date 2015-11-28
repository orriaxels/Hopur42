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
        void sort(int sortBy);   //setti sem void. Tharf mogulega ad breyta
        vector<int> search(const string searchString);
//		void remove();  ef timi gefst
//      void editEntery(); ef timi gefst

    private:  
        string makeSearchable(vector<Persons> list, int index);
    	//Takes vector of Persons and creates a single string to search for match
};

#endif // SERVICE_H
