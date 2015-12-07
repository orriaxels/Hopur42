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

//Set funcitons
void Persons::setFirst(const string firstName){
	firstname=firstName;
}
void Persons::setLast(const string lastName){
	lastname=lastName;
}
void Persons::setKnownFor(const string persknownFor){
	knownfor=persknownFor;
}
void Persons::setGender(const bool persGender){
	gender=persGender;
}
void Persons::setBorn(const int yBorn){
	yearBorn=yBorn;
}
void Persons::setDied(const int yDied){
	yearDied=yDied;
}
