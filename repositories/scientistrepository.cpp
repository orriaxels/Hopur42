#include <vector>
#include <string>
#include <QtSql>
#include <Qstring>

#include "scientistrepository.h"
#include "models/scientist.h"

Scientistrepository::Scientistrepository() {
  // default construct
}

bool Scientistrepository::addToDatabase(Scientist newScientist) {
  QSqlQuery query;

  QString fName  = QString::fromStdString((newScientist.getF()));
  QString lName  = QString::fromStdString((newScientist.getL()));
  bool    gender = newScientist.getGender();
  int     born   = newScientist.getYearBorn();
  int     died   = newScientist.getYearDied();
  QString known  = QString::fromStdString((newScientist.getKnownFor()));


  query.prepare("INSERT INTO Scientists (FirstName, LastName, Gender, Born, Died, KnownFor) "
                "VALUES (:FirstName, :LastName, :Gender, :Born, :Died, :KnownFor)");
  query.bindValue(":FirstName", fName);
  query.bindValue(":LastName",  lName);
  query.bindValue(":Gender",    gender);
  query.bindValue(":Born",      born);
  query.bindValue(":Died",      died);
  query.bindValue(":KnownFor",  known);

  return query.exec();
}

bool Scientistrepository::removeScientist(int idToRemove) {
  QSqlQuery query;

  query.prepare("UPDATE Scientists SET Deleted=1 WHERE id=:id");
  query.bindValue(":id", idToRemove);

  if (query.exec()) {
    if (removeRelationScientist(idToRemove)) {
      return true;
    }
    else {
      query.prepare("UPDATE Scientists SET Deleted=0 WHERE id=:id");
      query.bindValue(":id", idToRemove);
      query.exec();
    }
  }

  return false;
}

bool Scientistrepository::removeRelationScientist(int idScientistToRemove) {
  QSqlQuery query;

  query.prepare("UPDATE Relations SET Deleted = 1 WHERE idScientists=:idScientists");
  query.bindValue(":idScientists", idScientistToRemove);

  return query.exec();
}

vector<Scientist>Scientistrepository::searchScientist(QString searchString) {
  QSqlQuery query;
  scientistsList.clear();

  query.exec("SELECT * FROM Scientists WHERE FirstName  LIKE '%" + searchString + "%'"
             "OR LastName LIKE '%" + searchString + "%'"
             "OR Born LIKE '%" + searchString + "%'"
             "OR Died LIKE '%" + searchString + "%'"
             "OR KnownFor LIKE '%" + searchString + "%'");

  while (query.next()) {
    int    id     = query.value("id").toUInt();
    string fName  = query.value("FirstName").toString().toStdString();
    string lName  = query.value("LastName").toString().toStdString();
    bool   gender = query.value("Gender").toBool();
    int    born   = query.value("Born").toUInt();
    int    died   = query.value("Died").toUInt();
    string known  = query.value("KnownFor").toString().toStdString();

    Scientist scientFromList(id, fName, lName, gender, born, died, known);
    scientistsList.push_back(scientFromList);
  }
  return scientistsList;
}

vector<Scientist>Scientistrepository::getScientistList() {
  QSqlQuery query;

  scientistsList.clear();

  query.exec(
    "SELECT * FROM Scientists WHERE Deleted IN (0) ORDER BY FirstName ASC");

  while (query.next()) {
    int    id     = query.value("id").toUInt();
    string fName  = query.value("FirstName").toString().toStdString();
    string lName  = query.value("LastName").toString().toStdString();
    bool   gender = query.value("Gender").toBool();
    int    born   = query.value("Born").toUInt();
    int    died   = query.value("Died").toUInt();
    string known  = query.value("KnownFor").toString().toStdString();

    Scientist scientFromList(id, fName, lName, gender, born, died, known);
    scientistsList.push_back(scientFromList);
  }
  return scientistsList;
}

vector<Scientist>Scientistrepository::getAssociatedScientists(int idOfComputerToMatch) {
  QSqlQuery query;

  scientistsList.clear();

  query.prepare( "SELECT s.* FROM Relations r JOIN Scientists s "
                "ON s.id = r.idScientists WHERE r.idComputers = :idComputers");
  query.bindValue(":idComputers", idOfComputerToMatch);
  query.exec();

  while (query.next()) {
    int id        = query.value("id").toUInt();
    string fName  = query.value("FirstName").toString().toStdString();
    string lName  = query.value("LastName").toString().toStdString();
    bool   gender = query.value("Gender").toBool();
    int    born   = query.value("Born").toUInt();
    int    died   = query.value("Died").toUInt();
    string known  = query.value("KnownFor").toString().toStdString();

    Scientist scientFromList(id, fName, lName, gender, born, died, known);
    scientistsList.push_back(scientFromList);
  }
  return scientistsList;
}

bool Scientistrepository::addRelation(int idScientist, int idComputer) {
  QSqlQuery query;

  query.prepare( "INSERT INTO Relations (idComputers, idScientists) VALUES (:idComputers, :idScientists)");
  query.bindValue(":idComputers",  idComputer);
  query.bindValue(":idScientists", idScientist);


  return query.exec();
}

bool removeRelation(int idScientist, int idComputer){
    QSqlQuery query;

    query.prepare("UPDATE Relations SET Deleted = 1 WHERE idScientists=:idScientists AND idComputers=:idComputers");;
    query.bindValue(":idComputers",  idComputer);
    query.bindValue(":idScientists", idScientist);

    return query.exec();
}
