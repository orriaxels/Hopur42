#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <vector>
#include <string>
#include "persons.h"


class Repository  //Eina blokkin sem hefur bein samskipti vid .txt
{
public:
	Repository();
	void readFile();
	void writeToFile(); 
	vector<Persons> getList();
private:
	vector<Persons> list;

};

#endif // REPOSITORY_H
