#include <string>
#include <iostream>
#include "persons.h"

using namespace std;


Persons::Persons(){
	firstname="";
	lastname="";
	gender=0;
	yearBorn=0;//Jesus
	yearDied=0;
}

Persons::Persons(string fName, string lName, bool pGender, int born, int died, string KnownFor){
	firstname=fName;
	lastname=lName;
	gender=pGender;
	yearBorn=born;
	yearDied=died;
	knownfor=KnownFor;
}
Persons::Persons(int tableId, string fName, string lName, bool pGender, int born, int died, string KnownFor){
	persId=tableId;
	firstname=fName;
	lastname=lName;
	gender=pGender;
	yearBorn=born;
	yearDied=died;
	knownfor=KnownFor;
}

//get funcitons
int Persons::getId() const{
	return persId;
}
string Persons::getF() const{
	return firstname;
}
string Persons::getL() const{
	return lastname;
}
bool Persons::getGender() const{
    return gender;
}
string Persons::getKnownFor() const{
	return knownfor;
}
int Persons::getYearBorn() const{
	return yearBorn;
}
int Persons::getYearDied() const{
	return yearDied;
}

//set functions
bool Persons::setConnectWithComp(const vector<int> compId){
 	junctionWithComp.clear();
	junctionWithComp=compId;
}
