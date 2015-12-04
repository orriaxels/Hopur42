#include <iostream>
#include <vector>
#include <string>
#include <QtSql>

#include "repository.h"
#include "persons.h"

QSqlDatabase datab = QSqlDatabase::addDatabase("QSQLITE");


Repository::Repository(){
    //default construct
}

bool Repository::addToDatabase(Persons newPerson){

//	QSqlDatabase datab = QSqlDatabase::addDatabase("QSQLITE");
  datab.setDatabaseName("scientistandcomp.sqlite");
	datab.open();

  if (!datab.open()) {
    cout<< "Unable to connecto to database"<<endl<<endl;
		return false;
	}

	QSqlQuery query(datab);

	//Need to be variables to work with query.exec
	string fName = newPerson.getF();
	string lName = newPerson.getL();
	bool gender = newPerson.getGender();
	int born = newPerson.getYearBorn();
	int died = newPerson.getYearDied();
	string known = newPerson.getKnownFor();



	if(query.exec("INSERT INTO Scientists (FirstName, LastName, Gender, Born, Died, KnownFor) VALUES (fName, lName, gender, born, died, known)")){
		cout<<endl<<"Database updated."<<endl;
		datab.close();
		return true;
	}

	else{
		cout<<endl<<"Unable to write to database."<<endl;
		return false;
	}

}
// Ready needs new varnames.
// bool Repository::addToDatabase(Computer newComp){
//
// 	QSqlDatabase datab = QSqlDatabase::addDatabase("QSQLITE");
// 	datab.setDatabaseName("scientistandcomp.sqlite");
// datab.open();
//
// if (!datab.open()) {
// 	cout<< "Unable to connecto to database"<<endl<<endl;
// 	return false;
// }
//
// QSqlQuery query(datab);
//
// 	//Need to be variables to work with query.exec
// 	string name = newComp.getName();
// 	bool made  = newComp.getMade();
// 	int madeY = newComp.getMadeYear();
// 	int designedY = newComp.getDesignedYear();

//	datab.close();

// 	if(query.exec("INSERT INTO Computers (name, LastName, Gender, Born, Died, KnownFor) VALUES (fName, lName, gender, born, died, known)")){
// 		cout<<endl<<"Database updated."<<endl;
// 		return true;
// 	}
// 	else{
// 		cout<<endl<<"Unable to write to database."<<endl;
// 		return false;
// 	}
// }


vector<Persons> Repository::getScientistList(){

	datab.setDatabaseName("scientistandcomp.sqlite");
	datab.open();

	if (!datab.open()) {
		cout<< "Unable to connecto to database"<<endl<<endl;
	}

	QSqlQuery query(datab);

	query.exec("SELECT * FROM Scientists");
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
	datab.close();
//	QSqlDatabase::removeDatabase("scientistandcomp.sqlite");
	return scientistsList;
}

// vector<Computer> Repository::getComputerList(){
//while(query.next()){
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
//
// vector<Junction> Repository::getJunctionList(){
//while(query.next()){
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
//
