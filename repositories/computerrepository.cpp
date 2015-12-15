#include <vector>
#include <string>
#include <QtSql>
#include <Qstring>

#include "computerrepository.h"
#include "models/computer.h"

Computerrepository::Computerrepository() {}


bool Computerrepository::addToDatabase(Computer newComp) {
  QSqlQuery query;

  QString name       = QString::fromStdString((newComp.getName()));
  int     builtY     = newComp.getBuildYear();
  QString type       = QString::fromStdString((newComp.getType()));
  bool    builtOrNot = newComp.getBuild();

  query.prepare("INSERT INTO Computers (Name, YearBuilt, Type, BuiltOrNot) "
                "VALUES (:Name, :YearBuilt, :Type, :BuiltOrNot)");
  query.bindValue(":Name",       name);
  query.bindValue(":YearBuilt",  builtY);
  query.bindValue(":Type",       type);
  query.bindValue(":BuiltOrNot", builtOrNot);

  return query.exec();
}

bool Computerrepository::updateComputer(Computer computerUpdate){
  QSqlQuery query;

  int	   	id	       = computerUpdate.getId();
  QString name       = QString::fromStdString((computerUpdate.getName()));
  int     builtY     = computerUpdate.getBuildYear();
  QString type       = QString::fromStdString((computerUpdate.getType()));
  bool    builtOrNot = computerUpdate.getBuild();

  query.prepare("UPDATE Scientists SET Name=:Name, YearBuilt=:YearBuilt,
                                      Type=Type:, BuiltOrNot=:BuiltOrNot WHERE id=:id");
	query.bindValue(":id",		     id);
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

  query.exec("SELECT * FROM Computers WHERE (Name LIKE '%" + searchString + "%'"
                                        "OR Type LIKE '%" + searchString + "%'"
                                        "OR BuiltOrNot LIKE '%" + searchString + "%'"
                                        "OR YearBuilt LIKE '%" + searchString + "%')"
                                       "AND Deleted='0'");

  return queryComputerTable(query);
}

vector<Computer> Computerrepository::advancedSearchComputer(QString searchString){
	QSqlQuery query;

	query.exec("SELECT * FROM Computers WHERE " + searchString +
										 "AND Deleted='0'");

	return queryComputerTable(query);
}


vector<Computer> Computerrepository::getComputerList() {
  QSqlQuery query;

  query.exec("SELECT * FROM Computers WHERE Deleted IN (0) ORDER BY Name ASC");

  return queryComputerTable(query);
}

vector<Computer> Computerrepository::getAssociatedComputers(int idOfScientistToMatch) {
  QSqlQuery query;

  query.prepare("SELECT c.* FROM Relations r JOIN Computers c "
                "ON c.id = r.idComputers WHERE r.idScientists = :idScientist AND r.Deleted='0'");
  query.bindValue(":idScientist", idOfScientistToMatch);
  query.exec();

  return queryComputerTable(query);
}

vector<Computer> Computerrepository::queryComputerTable(QSqlQuery query){
	computerList.clear();
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
