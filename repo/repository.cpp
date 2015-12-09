#include <vector>
#include <string>
#include <QtSql>
#include <Qstring>
#include <iostream>

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
bool Repository::addRelation(int idPkComputer, int idPkScientists){
	QSqlQuery query;

	query.prepare("INSERT INTO Associate (scientist_id, comp_id) VALUES (:scientist_id, :comp_id)" );
	query.bindValue(":scientist_id", idPkScientists);
	query.bindValue(":comp_id", idPkComputer);
	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}

bool Repository::removePerson(int idToRemove){
	QSqlQuery query;
	query.prepare("UPDATE Scientists SET Deleted=1 WHERE id=:id");
	query.bindValue(":id", idToRemove);

	if( query.exec() ){
		return true;
	}
	else {
		return false;
	}
}
bool Repository::removeComputer(int idToRemove){
	QSqlQuery query;
	query.prepare("UPDATE Computers SET Deleted = 1 WHERE id = :id" );
	query.bindValue(":id", idToRemove);

	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}
bool Repository::removeRelation(int idScientist, int idComputer){
	QSqlQuery query;
	query.prepare("UPDATE Associate SET Deleted = 1 WHERE scientist_id=:scientist_id AND comp_id=:comp_id" );
	query.bindValue(":scientist_id", idScientist);
	query.bindValue(":comp_id", idComputer);
	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}
vector<Persons> Repository::searchScientist(string searchString){
	QSqlQuery query;
	QString qSearch = QString::fromStdString( (searchString.c_str()) );
	scientistsList.clear();

	query.prepare("SELECT * FROM Scientists WHERE FirstName LIKE :search OR LastName  LIKE :search OR Born  LIKE :search OR Died  LIKE :search OR KnownFor LIKE :search ");
	query.bindValue(":search", qSearch);
	query.exec();

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

vector<Persons> Repository::searchScientist(string searchString1, string searchString2){
	QSqlQuery query;
	QString qSearch1 = QString::fromStdString( (searchString1.c_str()) );
	QString qSearch2 = QString::fromStdString( (searchString2.c_str()) );
	scientistsList.clear();

	query.prepare("SELECT * FROM Scientists WHERE FirstName LIKE :search1 AND LastName LIKE :search2 ");
	query.bindValue(":search1", qSearch1);
	query.bindValue(":search2", qSearch2);
	query.exec();

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

vector<Computers> Repository::searchComputer(string searchString){
	QSqlQuery query;
	QString qSearch = QString::fromStdString( (searchString.c_str()) );
	computerList.clear();

	query.prepare("SELECT * FROM Computers WHERE Name LIKE :search OR Type LIKE :search OR Built_or_not LIKE :search OR Year_built LIKE :search");
	query.bindValue(":search", qSearch);
	query.exec();
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
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY  id DESC");
			else
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY id ASC");
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


vector<Persons> Repository::getAssociatedP(Computers findForComputer){
	QSqlQuery query;
	scientistsList.clear();

	int idComputer= findForComputer.getId();
	vector<int> idOfAssociatedScientists;


	query.prepare("SELECT * FROM Associate WHERE Deleted=0 AND comp_id=:comp_id");
	query.bindValue(":comp_id", idComputer);
	query.exec();

	while(query.next()){
		idOfAssociatedScientists.push_back( query.value("scientist_id").toUInt() );
	}

	//Gets computers with appropriate ID's from database
	for(unsigned int i=0; i< idOfAssociatedScientists.size(); i++){
		int idScientist=idOfAssociatedScientists.at(i);

		query.prepare("SELECT * FROM Scientists WHERE id=:id");
		query.bindValue(":id", idScientist);
		query.exec();

		query.first(); //.first because only one resault expected
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

vector<Computers> Repository::getAssociatedC(Persons findForPerson){
	computerList.clear();
	QSqlQuery query;
	int idPerson= findForPerson.getId();
	vector<int> idOfAssociatedComputers;

	query.prepare("SELECT * FROM Associate WHERE Deleted=0 AND scientist_id=:scientist_id");
	query.bindValue(":scientist_id", idPerson);
	query.exec();

	while(query.next()){
		idOfAssociatedComputers.push_back( query.value("comp_id").toUInt() );
	}

	//Gets computers with appropriate ID's from database
	for(unsigned int i=0; i< idOfAssociatedComputers.size(); i++){
		int idComp=idOfAssociatedComputers.at(i);

		query.prepare("SELECT * FROM Computers WHERE id=:id");
		query.bindValue(":id", idComp);
		query.exec();

		query.first(); //.first because only one resault expected
		int id= query.value("id").toUInt();
		string name = query.value("Name").toString().toStdString() ;
		string type = query.value("Type").toString().toStdString();
		bool builtOrNot  = query.value("Built_or_not").toUInt();
		int builtY = query.value("Year_built").toUInt();
		Computers newComp(id, name, type, builtOrNot, builtY);
		computerList.push_back(newComp);

	}
	return computerList;
}
