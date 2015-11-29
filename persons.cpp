#include <string>
#include <iostream>
#include "persons.h"

using namespace std;


Persons::Persons(){
	firstname="";
	lastname="";
	yearBorn=0;//Jesus 
	yearDied=33; // Jesus died at 33	
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

string Persons::getF(){
	retrun firstname;
}

string Persons::getL(){
	return lastname;
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
