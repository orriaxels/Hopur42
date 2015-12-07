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
Computers::Computers(string cName, string cType, bool build, int bldYear){
	computername = cName;
	computertype = cType;
	ifBuild = build;
	buildyear = bldYear;
}
Computers::Computers(int tableId, string cName, string cType, bool build, int bldYear){
	compId=tableId;
	computername = cName;
	computertype = cType;
	ifBuild = build;
	buildyear = bldYear;
}

// Get functions
string Computers::getName() const{
	return computername;
}

string Computers::getType() const{
	return computertype;
}

bool Computers::getBuild() const{
	return ifBuild;
}

int Computers::getBuildYear() const{
	return buildyear;
}

// // Set functions
// void Computers::setName(const string computerName){
// 	computername = computerName;
// }
//
// void Computers::setType(const string computerType){
// 	computertype = computerType;
// }
//
// void Computers::setBuild(const bool build){
// 	ifBuild = build;
// }
//
// void Computers::setBuildYear(const int buildYear){
// 	buildyear = buildYear;
// }
