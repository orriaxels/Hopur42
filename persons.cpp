#include <string>
#include <iostream>
#include "persons.h"

using namespace std;


Persons::Persons(){
//Default constructor
    firstname="";
    lastname="";
    yearBorn=0;//Jesus
    yearDied=33; // Jesus died at 33
}

Persons::Persons(string fName, string lName, int born, int died){
//Constructor without quote
    firstname=fName;
    lastname=lName;
    yearBorn=born;
    yearDied=died;
}

Persons::Persons(string fName, string lName, int born, int died, string Quote){
//Constructor with quote
    firstname=fName;
    lastname=lName;
    yearBorn=born;
    yearDied=died;
    quote=Quote;
}

string Persons::getF(sting firstname){
    firstname = firstname;

    retrun firstname;
}

string Persons::getL(sting lastname){
    lastname = lastname;

    return lastname;
}
string Persons::getQuote(sting quote){
    quote = qoute;
    return quote;
}
bool Persons::getGender(bool gender){
    gender = gender;

    return gender;
}
int Persons::getYearBorn(int yearborn){
    yearborn = yearborn

    return yearBorn;
}
int Persons::getYearDied(int yeardied){
    yeardied = yeardied;

    return yearDied;
}


