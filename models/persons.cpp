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

//get funcitons
string Persons::getF(){
	return firstname;
}
string Persons::getL(){
	return lastname;
}
bool Persons::getGender(){
    return gender;
}
string Persons::getKnownFor(){
	return knownfor;
}
int Persons::getYearBorn(){
	return yearBorn;
}
int Persons::getYearDied(){
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
