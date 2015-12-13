#include "relationrepository.h"
#include <QtSql>

Relationrepository::Relationrepository()
{}

bool Relationrepository::addRelation(int idScientist, int idComputer) {
  QSqlQuery query;

  // To check if record exists but marked as deleted
  query.prepare("Select * From Relations WHERE idComputers = :idComputers"
                "AND idScientists = :idScientists");
  query.bindValue(":idComputers",  idComputer);
  query.bindValue(":idScientists", idScientist);

  if (query.isValid()) {
    query.prepare("UPDATE Relations SET Deleted = 0 WHERE idScientists=:idScientists "
                  "AND idComputers=:idComputers");
    query.bindValue(":idComputers",  idComputer);
    query.bindValue(":idScientists", idScientist);

    return query.exec();
  }

  query.prepare(
    "INSERT INTO Relations (idComputers, idScientists) VALUES (:idComputers, :idScientists)");
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
