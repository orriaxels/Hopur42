#include <vector>
#include <string>
#include <QtSql>
#include <Qstring>

#include "repo/repository.h"
#include "models/scientist.h"
#include "models/computer.h"

Repository::Repository(){
    //default construct
}

bool Repository::addToDatabase(Scientist newScientist){
	QSqlQuery query;

	//Need to be variables to work with query.exec
	QString fName = QString::fromStdString( (newScientist.getF()).c_str() ); //bindvalue needs QString
	QString lName = QString::fromStdString( (newScientist.getL()).c_str() ); //bindvalue needs QString
	bool gender = newScientist.getGender();
	int born = newScientist.getYearBorn();
	int died = newScientist.getYearDied();
	QString known = QString::fromStdString( (newScientist.getKnownFor()).c_str() );

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

bool Repository::addToDatabase(Computer newComp){
	QSqlQuery query;

	//Need to be variables to work with query.exec
	QString name = QString::fromStdString( ( newComp.getName() ).c_str() );//bindvalue needs QString
	int builtY = newComp.getBuildYear();
	QString type = QString::fromStdString( ( newComp.getType() ).c_str() );//bindvalue needs QString
	bool builtOrNot  = newComp.getBuild();


	query.prepare("INSERT INTO Computers (Name, YearBuilt, Type, BuiltOrNot) VALUES (:Name, :YearBuilt, :Type, :BuiltOrNot)" );
  query.bindValue(":Name", name);
	query.bindValue(":YearBuilt", builtY);
	query.bindValue(":Type", type);
	query.bindValue(":BuiltOrNot", builtOrNot);
	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}

bool Repository::addRelation(int idPkComputer, int idPkScientists){
	QSqlQuery query;

	query.prepare("INSERT INTO Associate (scientistID, compID) VALUES (:scientistID, :compID)" );
	query.bindValue(":scientistID", idPkScientists);
	query.bindValue(":compID", idPkComputer);
	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}



bool Repository::removeScientist(int idToRemove){
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
	query.prepare("UPDATE Associate SET Deleted = 1 WHERE scientistID=:scientistID AND compID=:compID" );
	query.bindValue(":scientistID", idScientist);
	query.bindValue(":compID", idComputer);
	if( query.exec() ){
		return true;
	}
	else{
		return false;
	}
}



vector<Scientist> Repository::searchScientist(string searchString){
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

		Scientist scientFromList(id, fName, lName, gender, born, died, known);
		scientistsList.push_back(scientFromList);
	}
	return scientistsList;
}

vector<Scientist> Repository::searchScientist(string searchString1, string searchString2){
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

		Scientist scientFromList(id, fName, lName, gender, born, died, known);
		scientistsList.push_back(scientFromList);
	}
	return scientistsList;
}

vector<Computer> Repository::searchComputer(string searchString){
	QSqlQuery query;
	QString qSearch = QString::fromStdString( (searchString.c_str()) );
	computerList.clear();

	query.prepare("SELECT * FROM Computers WHERE Name LIKE :search OR Type LIKE :search OR BuiltOrNot LIKE :search OR YearBuilt LIKE :search");
	query.bindValue(":search", qSearch);
	query.exec();
	while(query.next()){
		int id= query.value("id").toUInt();
		string name = query.value("Name").toString().toStdString();
		string type = query.value("Type").toString().toStdString();
		bool builtOrNot  = query.value("BuiltOrNot").toUInt();
		int builtY = query.value("YearBuilt").toUInt();

		Computer newComp(id, name, type, builtOrNot, builtY);
		computerList.push_back(newComp);
	}
	return computerList;
}



vector<Scientist> Repository::getScientistList(int byColumn, bool aceDesc){

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

		Scientist scientFromList(id, fName, lName, gender, born, died, known);
		scientistsList.push_back(scientFromList);
	}
	return scientistsList;
}

vector<Computer> Repository::getComputerList(int byColumn, bool aceDesc){

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
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY BuiltOrNot DESC");
			else
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY BuiltOrNot ASC");
			break;
		case 4:
			if(aceDesc)
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY YearBuilt DESC");
			else
				query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY YearBuilt ASC");
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
		bool builtOrNot  = query.value("BuiltOrNot").toUInt();
		int builtY = query.value("YearBuilt").toUInt();

		Computer newComp(id, name, type, builtOrNot, builtY);
		computerList.push_back(newComp);
  }
	return computerList;
}



vector<Scientist> Repository::getAssociatedP(Computer findForComputer){
	QSqlQuery query;
	scientistsList.clear();

	int idComputer= findForComputer.getId();
	vector<int> idOfAssociatedScientists;


	query.prepare("SELECT * FROM Associate WHERE Deleted=0 AND compID=:compID");
	query.bindValue(":compID", idComputer);
	query.exec();

	while(query.next()){
		idOfAssociatedScientists.push_back( query.value("scientistID").toUInt() );
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

		Scientist scientFromList(id, fName, lName, gender, born, died, known);
		scientistsList.push_back(scientFromList);
	}
	return scientistsList;
}

vector<Computer> Repository::getAssociatedC(Scientist findForScientist){
	computerList.clear();
	QSqlQuery query;
	int idScientist= findForScientist.getId();
	vector<int> idOfAssociatedComputers;

	query.prepare("SELECT * FROM Associate WHERE Deleted=0 AND scientistID=:scientistID");
	query.bindValue(":scientistID", idScientist);
	query.exec();

	while(query.next()){
		idOfAssociatedComputers.push_back( query.value("compID").toUInt() );
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
		bool builtOrNot  = query.value("BuiltOrNot").toUInt();
		int builtY = query.value("YearBuilt").toUInt();
		Computer newComp(id, name, type, builtOrNot, builtY);
		computerList.push_back(newComp);

	}
	return computerList;
}
