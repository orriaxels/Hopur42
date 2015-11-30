#include <string>
#include <iostream>
#include "persons.h"

using namespace std;


Persons::Persons(){
	firstname="";
	lastname="";
	yearBorn=0;//Jesus 
	yearDied=0; 
}

Persons::Persons(string fName, string lName, int born, int died){
	firstname=fName;
	lastname=lName;
	yearBorn=born; 
	yearDied=died;	
}

Persons::Persons(string fName, string lName, int born, int died, string Quote){
	firstname=fName;
	lastname=lName;
	yearBorn=born; 
	yearDied=died;
	quote=Quote;	
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
string Persons::getQuote(){
	return quote;
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
void Persons::setQuote(const string persQuote){
	quote=persQuote;
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
