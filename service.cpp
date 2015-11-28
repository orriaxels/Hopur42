#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "service.h"
#include "interface.h"
#include "persons.h"
#include "repository.h"

using namespace std;

Service::Service(){//default constructor

}

//fer eftir hvernig vid prentum ut i interface
void Service::sort(int sortBy){
//    Repository
//	vector<Persons> bufferList;
//	bufferList=repository::getlist();


}

vector<int> Service::search(const string searchString){ //Ekki leitad i quote
    Repository repoVar;
    string buffer;
    vector<Persons> list=repoVar.getList();
    vector<int> foundIn;

    for(unsigned int i=0; i < list.size(); i++){
    	buffer=makeSearchable(list, i);
    	if (buffer.find(searchString) != string::npos) {
    		foundIn.push_back(i);
		}
    }

    return foundIn;
}

string Service::makeSearchable(vector<Persons> list, int index){

    string searchable="";
	ostringstream stringstream;

    searchable=list.at(index).getF();
	searchable+="\t" ;		//svo ekki finnist stafir tar sem skett er saman

    searchable+=list.at(index).getL();
	searchable+="\t" ;

    stringstream << list.at(index).getYearBorn();
	searchable+=stringstream.str();
    stringstream.str("");
	searchable+="\t"; 

    stringstream << list.at(index).getYearDied();
	searchable+=stringstream.str();

	return searchable;
}



/*
void Service::remove()  ef timi gefst
{

}
void Service::editEntery()  ef timi gefst
{

}
*/
