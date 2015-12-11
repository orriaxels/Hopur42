#include "repositories/computerrepository.h"
#include "models/computer.h"
#include "models/scientist.h"
#include <vector>
#include <string>
#include <QtSql>
#include <Qstring>

Computerrepository::Computerrepository(){}


bool Computerrepository::addToDatabase(Computer newComp){}


bool Computerrepository::addRelation(int idPkComputer, int idPkScientists){}

bool Computerrepository::removeComputer(int idToRemove){}
bool Computerrepository::removeRelation(int idScientist, int idComputer){}


vector<Computer> Computerrepository::searchComputer(string searchString){}

vector<Computer> Computerrepository::getComputerList(int byColumn, bool aceDesc){


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


