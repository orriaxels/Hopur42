#include <iostream>
#include <string>
#include "computers.h"

using namespace std;

Computers::Computers(){
	computername = "";
	computertype = "";
	ifBuild = 0;
	buildyear = 0;

}

// Get functions
Computers(string cName, string cType, bool build, int bldYear){
	computername = cName;
	computertype = cType;
	ifBuild = build;
	buildyear = bldYear;
}

string Computers::getName(){
	return computername;
}

string Computers::getType(){
	return computertype;
}

bool Computers::getBuild(){
	return ifBuild;
}

int Computers::getBuildYear(){
	return buildyear;
}

// Set functions
void Computers::setName(const string computerName){
	computername = computerName;
}

void Computers::setType(const string computerType){
	computertype = computerType;
}

void Computers::setBuild(const bool build){
	ifBuild = build;
}

void Computers::setBuildYear(const int buildYear){
	buildyear = buildYear;
}