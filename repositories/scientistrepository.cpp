#include "scientistrepository.h"

#include "models/scientist.h"
#include <vector>
#include <string>
#include <sstream>
#include <QtSql>
#include <Qstring>

Scientistrepository::Scientistrepository(){
    //default construct
}

bool Scientistrepository::addToDatabase(Scientist newScientist){
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


bool Scientistrepository::addRelation(int idPkComputer, int idPkScientists){
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



bool Scientistrepository::removeScientist(int idToRemove){
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


bool Scientistrepository::removeRelation(int idScientist, int idComputer){
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



vector<Scientist> Scientistrepository::searchScientist(QString searchString){
	QSqlQuery query;
	scientistsList.clear();



	//	query.prepare("SELECT * FROM Scientists WHERE FirstName LIKE '%" << searchString << "%' ");
	//    query.bindValue(":search", searchString);

        query.exec( "SELECT * FROM Scientists WHERE FirstName  LIKE '%" + searchString+ "%'" );

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


vector<Scientist> Scientistrepository::getScientistList(int byColumn, bool aceDesc){

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




//vector<Scientist> Scientistrepository::getAssociatedP(Computer findForComputer){
//	QSqlQuery query;
//	scientistsList.clear();

//	int idComputer= findForComputer.getId();
//	vector<int> idOfAssociatedScientists;


//	query.prepare("SELECT * FROM Associate WHERE Deleted=0 AND compID=:compID");
//	query.bindValue(":compID", idComputer);
//	query.exec();

//	while(query.next()){
//		idOfAssociatedScientists.push_back( query.value("scientistID").toUInt() );
//	}

//	//Gets computers with appropriate ID's from database
//	for(unsigned int i=0; i< idOfAssociatedScientists.size(); i++){
//		int idScientist=idOfAssociatedScientists.at(i);

//		query.prepare("SELECT * FROM Scientists WHERE id=:id");
//		query.bindValue(":id", idScientist);
//		query.exec();

//		query.first(); //.first because only one resault expected
//		int id = query.value("id").toUInt();
//		string fName = query.value("FirstName").toString().toStdString();
//		string lName = query.value("LastName").toString().toStdString();
//		bool gender = query.value("Gender").toBool();
//		int born = query.value("Born").toUInt();
//		int died = query.value("Died").toUInt();
//		string known = query.value("KnownFor").toString().toStdString();

//		Scientist scientFromList(id, fName, lName, gender, born, died, known);
//		scientistsList.push_back(scientFromList);
//	}
//	return scientistsList;
//}
