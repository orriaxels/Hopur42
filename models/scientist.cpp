#include <string>
#include "scientist.h"

Scientist::Scientist(){
	firstName="";
	lastName="";
	gender=0;
	yearBorn=0;//Jesus
	yearDied=0;
}

Scientist::Scientist(string fName, string lName, bool pGender, int born, int died, string KnownFor){
	firstName=fName;
	lastName=lName;
	gender=pGender;
	yearBorn=born;
	yearDied=died;
	knownFor=KnownFor;
}

Scientist::Scientist(int tableId, string fName, string lName, bool pGender, int born, int died, string KnownFor){
	persId=tableId;
	firstName=fName;
	lastName=lName;
	gender=pGender;
	yearBorn=born;
	yearDied=died;
	knownFor=KnownFor;
}

//get funcitons
int Scientist::getId() const{
	return persId;
}

string Scientist::getF() const{
	return firstName;
}

string Scientist::getL() const{
	return lastName;
}

bool Scientist::getGender() const{
    return gender;
}

string Scientist::getKnownFor() const{
	return knownFor;
}

int Scientist::getYearBorn() const{
	return yearBorn;
}

int Scientist::getYearDied() const{
	return yearDied;
}
