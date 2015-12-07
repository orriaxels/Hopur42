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

vector<Persons> Repository::getScientistList(int byColumn, bool aceDesc){

	QSqlQuery query;
	scientistsList.clear();

	switch(byColumn){  //Order by does not work with string, thus query commands in case
		case 1:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists ORDER BY FirstName DESC");
			else
				query.exec("SELECT * FROM Scientists ORDER BY FirstName ASC");
			break;
		case 2:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists ORDER BY LastName DESC");
			else
				query.exec("SELECT * FROM Scientists ORDER BY LastName ASC");
			break;
		case 3:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists ORDER BY GenderGender DESC");
			else
				query.exec("SELECT * FROM Scientists ORDER BY Gender ASC");
			break;
		case 4:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists ORDER BY Born DESC");
			else
				query.exec("SELECT * FROM Scientists ORDER BY Born ASC");
			break;
		case 5:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists ORDER BY Died DESC");
			else
				query.exec("SELECT * FROM Scientists ORDER BY Died ASC");
			break;
		default:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists ORDER BY rowid DESC");
			else
				query.exec("SELECT * FROM Scientists ORDER BY rowid ASC");
			break;
	}

	while(query.next()){
		int id=query.value("rowid").toUInt();
		string fName = query.value("FirstName").toString().toStdString();
		string lName = query.value("LastName").toString().toStdString();
		bool gender = query.value("Gender").toBool();
		int born = query.value("Born").toUInt();
		int died = query.value("Died").toUInt();
		string known = query.value("KnownFor").toString().toStdString();

		Persons perFromList(id, fName, lName, gender, born, died, known);
		scientistsList.push_back(perFromList);
	}

	return scientistsList;
}

vector<Computers> Repository::getComputerList(int byColumn, bool aceDesc){

	QSqlQuery query;
	computerList.clear();

	switch(byColumn){
		case 1:
			if(aceDesc)
				query.exec("SELECT * FROM Computers ORDER BY Name DESC");
			else
			query.exec("SELECT * FROM Computers ORDER BY Name ASC");
			break;
		case 2:
			if(aceDesc)
				query.exec("SELECT * FROM Computers ORDER BY Type DESC");
			else
				query.exec("SELECT * FROM Computers ORDER BY Type ASC");
			break;
		case 3:
			if(aceDesc)
				query.exec("SELECT * FROM Computers ORDER BY Built_or_not DESC");
			else
				query.exec("SELECT * FROM Computers ORDER BY Built_or_not ASC");
			break;
		case 4:
			if(aceDesc)
				query.exec("SELECT * FROM Computers ORDER BY Year_built DESC");
			else
				query.exec("SELECT * FROM Computers ORDER BY Year_built ASC");
			break;
		default:
			if(aceDesc)
				query.exec("SELECT * FROM Computers ORDER BY rowid DESC");
			else
				query.exec("SELECT * FROM Computers ORDER BY rowid ASC");
			break;
	}

  while(query.next()){
		int id=query.value("rowid").toUInt();
		string name = query.value("Name").toString().toStdString();
		string type = query.value("Type").toString().toStdString();
		bool builtOrNot  = query.value("Built_or_not").toUInt();
		int builtY = query.value("Year_built").toUInt();

		Computers newComp(id, name, type, builtOrNot, builtY);
		computerList.push_back(newComp);
  }
	return computerList;
}
