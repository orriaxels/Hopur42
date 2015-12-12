#include <vector>
#include <string>
#include <QtSql>
#include <Qstring>

#include "computerrepository.h"
#include "models/computer.h"

Computerrepository::Computerrepository() {}


bool Computerrepository::addToDatabase(Computer newComp) {
  QSqlQuery query;

  QString name       = QString::fromStdString((newComp.getName()).c_str());
  int     builtY     = newComp.getBuildYear();
  QString type       = QString::fromStdString((newComp.getType()).c_str());
  bool    builtOrNot = newComp.getBuild();

  query.prepare("INSERT INTO Computers (Name, YearBuilt, Type, BuiltOrNot) "
                "VALUES (:Name, :YearBuilt, :Type, :BuiltOrNot)");
  query.bindValue(":Name",       name);
  query.bindValue(":YearBuilt",  builtY);
  query.bindValue(":Type",       type);
  query.bindValue(":BuiltOrNot", builtOrNot);

  return query.exec();
}

bool Computerrepository::removeComputer(int idToRemove) {
  QSqlQuery query;

  query.prepare("UPDATE Computers SET Deleted=1 WHERE id=:id");
  query.bindValue(":id", idToRemove);

  if (query.exec()) {
    if (removeRelationComputers(idToRemove)) {
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

bool Computerrepository::removeRelationComputers(int idComputerToRemove) {
  QSqlQuery query;

  query.prepare("UPDATE Relations SET Deleted = 1 WHERE idComputers=:idComputers");
  query.bindValue(":idComputers", idComputerToRemove);

  return query.exec();
}

vector<Computer> Computerrepository::searchComputer(QString searchString) {
  QSqlQuery query;

  computerList.clear();

  query.exec("SELECT * FROM Computers WHERE Name LIKE '%" + searchString + "%'"
                                        "OR Type LIKE '%" + searchString + "%'"
                                        "OR BuiltOrNot LIKE '%" + searchString + "%'"
                                        "OR YearBuilt LIKE '%" + searchString + "%'"
                                       "AND Deleted=0");

  while (query.next()) {
    int id            = query.value("id").toUInt();
    string name       = query.value("Name").toString().toStdString();
    string type       = query.value("Type").toString().toStdString();
    bool   builtOrNot = query.value("BuiltOrNot").toUInt();
    int    builtY     = query.value("YearBuilt").toUInt();

    Computer newComp(id, name, type, builtOrNot, builtY);
    computerList.push_back(newComp);
  }
  return computerList;
}

vector<Computer> Computerrepository::getComputerList() {
  QSqlQuery query;

  computerList.clear();

  query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Name ASC");

  while (query.next()) {
    int id            = query.value("id").toUInt();
    string name       = query.value("Name").toString().toStdString();
    string type       = query.value("Type").toString().toStdString();
    bool   builtOrNot = query.value("BuiltOrNot").toUInt();
    int    builtY     = query.value("YearBuilt").toUInt();

    Computer newComp(id, name, type, builtOrNot, builtY);
    computerList.push_back(newComp);
  }
  return computerList;
}

vector<Computer> Computerrepository::getAssociatedComputers(int idOfScientistToMatch) {
  QSqlQuery query;

  computerList.clear();

  query.prepare("SELECT c.* FROM Relations r JOIN Computers c "
                "ON c.id = r.idComputers WHERE r.idScientist = :idScientist");
  query.bindValue(":idScientist", idOfScientistToMatch);
  query.exec();

  while (query.next()) {
    int id            = query.value("id").toUInt();
    string name       = query.value("Name").toString().toStdString();
    string type       = query.value("Type").toString().toStdString();
    bool   builtOrNot = query.value("BuiltOrNot").toUInt();
    int    builtY     = query.value("YearBuilt").toUInt();

    Computer newComp(id, name, type, builtOrNot, builtY);
    computerList.push_back(newComp);
  }
  return computerList;
}
