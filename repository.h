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
	void readFile();  						//reads in from file into private var
	void writeToFile(Persons newPerson); 	//adds new Person object to end of file
	vector<Persons> getList();				//returns list from file
	void backupList(vector<Persons> listBackup); //backs up list if somthing fails during remove
	void rewriteList(vector<Persons> listnew);   //Rewrites file completly. Used to rewrite with one or more removed
private:
	vector<Persons> list;	//contains list of all Persons in file
    int convertToInt(string strConvert);  //casts strings with numbers to Int var and returns

};

#endif // REPOSITORY_H
