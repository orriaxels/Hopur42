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
	void readFile();  //reads in from file into private var
	void writeToFile(Persons newwPerson); //adds to end of file new line
	vector<Persons> getList();
private:
	vector<Persons> list;

};

#endif // REPOSITORY_H
