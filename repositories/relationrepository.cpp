#include "relationrepository.h"
#include <QtSql>

Relationrepository::Relationrepository()
{}

bool Relationrepository::addRelation(int idScientist, int idComputer) {
   QSqlQuery query;

	query.prepare( "INSERT INTO Relations (idComputers, idScientists) VALUES (:idComputers, :idScientists)");
	query.bindValue(":idComputers",  idComputer);
	query.bindValue(":idScientists", idScientist);
  	query.exec();

	query.prepare("UPDATE Relations SET Deleted = 0  WHERE idScientists=:idScientists "
				  "AND idComputers=:idComputers");
	query.bindValue(":idComputers",  idComputer);
	query.bindValue(":idScientists", idScientist);


  return query.exec();
}

bool Relationrepository::removeRelation(int idScientist, int idComputer) {
  QSqlQuery query;

  query.prepare(
    "UPDATE Relations SET Deleted = 1 WHERE idScientists=:idScientists AND idComputers=:idComputers");
  query.bindValue(":idComputers",  idComputer);
  query.bindValue(":idScientists", idScientist);

  return query.exec();
}

int Relationrepository::sizeOfTable(){
  QSqlQuery query;
  int sizeOfTable=0;

  query.exec("SELECT * FROM Relations WHERE Deleted = '0'");

  while (query.next()) {
	  sizeOfTable++;
  }
  return sizeOfTable;
}
