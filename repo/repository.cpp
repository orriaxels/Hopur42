#include <vector>
#include <string>
#include <QtSql>
#include <Qstring>

#include "repo/repository.h"
#include "models/persons.h"
#include "models/computers.h"

Repository::Repository(){
    //default construct
}

bool Repository::addToDatabase(Persons newPerson){

	QSqlQuery query;

	//Need to be variables to work with query.exec
	QString fName = QString::fromStdString( (newPerson.getF()).c_str() ); //bindvalue needs QString
	QString lName = QString::fromStdString( (newPerson.getL()).c_str() );
	bool gender = newPerson.getGender();
	int born = newPerson.getYearBorn();
	int died = newPerson.getYearDied();
	QString known = QString::fromStdString( (newPerson.getKnownFor()).c_str() );

	query.prepare("INSERT INTO Scientists (FirstName, LastName, Gender, Born, Died, KnownFor) VALUES (:FirstName, :LastName, :Gender, :Born, :Died, :KnownFor)" );
  query.bindValue(":FirstName", fName);
	query.bindValue(":LastName", lName);
	query.bindValue(":Gender", gender);
	query.bindValue(":Born", born);
	query.bindValue(":Died", died);
	query.bindValue(":KnownFor", known);
	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}

bool Repository::addToDatabase(Computers newComp){
	QSqlQuery query;

	//Need to be variables to work with query.exec
	QString name = QString::fromStdString( ( newComp.getName() ).c_str() );
	int builtY = newComp.getBuildYear();
	QString type = QString::fromStdString( ( newComp.getType() ).c_str() );
	bool builtOrNot  = newComp.getBuild();


	query.prepare("INSERT INTO Computers (Name, Year_built, Type, Built_or_not) VALUES (:Name, :Year_built, :Type, :Built_or_not)" );
  query.bindValue(":Name", name);
	query.bindValue(":Year_built", builtY);
	query.bindValue(":Type", type);
	query.bindValue(":Built_or_not", builtOrNot);
	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}

bool Repository::removePerson(int enteryToRemoveId){
	QSqlQuery query;
	query.prepare("UPDATE Scientists SET Deleted=1 WHERE id=:id");
	query.bindValue(":id", enteryToRemoveId);

	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}

bool Repository::removeComputer(int enteryToRemoveId){
	QSqlQuery query;
	query.prepare("UPDATE Computers SET Deleted = 1 WHERE id = :rowid" );
	query.bindValue(":rowid", enteryToRemoveId);

	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}

vector<Persons> Repository::getScientistList(int byColumn, bool aceDesc){

	QSqlQuery query;
	scientistsList.clear();

	switch(byColumn){  //Order by does not work with string, thus query commands in case
		case 1:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY FirstName DESC");
			else
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY FirstName ASC");
			break;
		case 2:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY LastName DESC");
			else
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY LastName ASC");
			break;
		case 3:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY GenderGender DESC");
			else
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY Gender ASC");
			break;
		case 4:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY Born DESC");
			else
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY Born ASC");
			break;
		case 5:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY Died DESC");
			else
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY Died ASC");
			break;
		default:
			if(aceDesc)
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY id DESC");
			else
				query.exec("SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY id ASC");
			break;
	}

	while(query.next()){
		int id = query.value("id").toUInt();
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
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Name DESC");
			else
			query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Name ASC");
			break;
		case 2:
			if(aceDesc)
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Type DESC");
			else
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Type ASC");
			break;
		case 3:
			if(aceDesc)
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Built_or_not DESC");
			else
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Built_or_not ASC");
			break;
		case 4:
			if(aceDesc)
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Year_built DESC");
			else
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Year_built ASC");
			break;
		default:
			if(aceDesc)
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY rowid DESC");
			else
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY rowid ASC");
			break;
	}

  while(query.next()){
		int id= query.value("id").toUInt();
		string name = query.value("Name").toString().toStdString();
		string type = query.value("Type").toString().toStdString();
		bool builtOrNot  = query.value("Built_or_not").toUInt();
		int builtY = query.value("Year_built").toUInt();

		Computers newComp(id, name, type, builtOrNot, builtY);
		computerList.push_back(newComp);
  }
	return computerList;
}
