#include <vector>
#include <string>
#include <QtSql>

#include "repo/repository.h"
#include "models/persons.h"
#include "models/computers.h"

Repository::Repository(){
    //default construct
}

bool Repository::addToDatabase(Persons newPerson){

	QSqlQuery query;

	//Need to be variables to work with query.exec
	string fName = newPerson.getF();
	string lName = newPerson.getL();
	bool gender = newPerson.getGender();
	int born = newPerson.getYearBorn();
	int died = newPerson.getYearDied();
	string known = newPerson.getKnownFor();

	if(query.exec("INSERT INTO scientists (FirstName, LastName, Gender, Born, Died, KnownFor) VALUES (fName, lName, gender, born, died, known)")){
		cout<<endl<<"Database updated."<<endl;
		return true;
	}

	else{
		cout<<endl<<"Unable to write to database."<<endl;
		return false;
	}
}

bool Repository::addToDatabase(Computers newComp){
	QSqlQuery query;

	//Need to be variables to work with query.exec
	string name = newComp.getName();
	string type = newComp.getType();
	bool builtOrNot  = newComp.getBuild();
	int builtY = newComp.getBuildYear();

	if(query.exec("INSERT INTO Computers (Name, Year_built, Type, Built_or_not) VALUES (name, builtY,type, builtOrNot)")){
		cout<<endl<<"Database updated."<<endl;
		return true;
	}
	else{
		cout<<endl<<"Unable to write to database."<<endl;
		return false;
	}
}

vector<Persons> Repository::getScientistList(){

	QSqlQuery query;

	query.exec("SELECT * FROM scientists");
	while(query.next()){
		string fName = query.value("FirstName").toString().toStdString();
		string lName = query.value("LastName").toString().toStdString();
		bool gender = query.value("Gender").toBool();
		int born = query.value("Born").toUInt();
		int died = query.value("Died").toUInt();
		string known = query.value("KnownFor").toString().toStdString();

		Persons perFromList(fName, lName, gender, born, died, known);
		scientistsList.push_back(perFromList);
	}

	return scientistsList;
}

vector<Computers> Repository::getComputerList(){

	QSqlQuery query;
	int i=0;
	query.exec("SELECT * FROM Computers");
  while(query.next()){
		string name = query.value("Name").toString().toStdString();
		string type = query.value("Type").toString().toStdString();
		bool builtOrNot  = query.value("Built_or_not").toUInt();
		int builtY = query.value("Year_built").toUInt();

		Computers newComp(name, type, builtOrNot, builtY);
		computerList.push_back(newComp);
  }
	return computerList;
}

// vector<Junction> Repository::getJunctionList(){
// while(query.next()){
// 	int id = query.value("id").toUInt();
// 	string name = query.value("First name").toString().toStdString();
// 	name += query.value("Last name").toString().toStdString();
// 	bool gender = query.value("Gender").toUInt();
// 	int born = query.value("Born").toUInt();
// 	int died = query.value("Died").toUInt();
// 	string known = query.value("Known for").toString().toStdString();
//
// 	cout<< id<<"  "<< name<<"  "<< gender<<"  "<<born<<"  "<<died<<"  "<<endl;
// }
// }
