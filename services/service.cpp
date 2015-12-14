#include <vector>
#include <string>
#include <sstream>
#include <QStringList>
#include <QString>

#include "service.h"
#include "repositories/computerrepository.h"
#include "repositories/scientistrepository.h"
#include "models/computer.h"
#include "models/scientist.h"

Service::Service() {} // default constructor

vector<Scientist>Service::getSortedScientistList() {
  return scientistRepository.getScientistList();
}

vector<Computer>Service::getSortedComputerList() {
  return computerRepository.getComputerList();
}

vector<Scientist>Service::searchScientists(QString searchString) {
  searchString = searchString.simplified();
  QStringList list = searchString.split(" ");
  vector<Scientist> bufferFound;
  bool isUnique = true;

  if (searchString.size() == 0) {
    return scientistRepository.getScientistList();
  }
  else if (list.at(0) == "??") {
    searchString.remove(QChar('?'));
    searchString.replace(QString("First name"), QString("FirstName"), Qt::CaseInsensitive);
    searchString.replace(QString("Last name"),  QString("LastName"),  Qt::CaseInsensitive);
    searchString.replace(QString("Known for"),  QString("KnownFor"),  Qt::CaseInsensitive);
    return scientistRepository.advancedSearchScientist(searchString);
  }
  else {
    // To search for each word indivudally and only return unique objects
    for (int i = 0; i < list.size(); i++) {
      vector<Scientist> buffer = scientistRepository.searchScientist(list.at(i));

      for (int j = 0; j < buffer.size(); j++) {
        for (int k = 0; k < bufferFound.size(); k++) {
          if ((buffer.at(j)).getId() == (bufferFound.at(k)).getId()) {
            isUnique = false;
          }
        }

        if (isUnique) {
          bufferFound.push_back(buffer.at(j));
        }
        isUnique = true;
      }
    }
    return bufferFound;
  }
}

vector<Computer>Service::searchComputers(QString searchString) {
  searchString = searchString.simplified();
  QStringList list = searchString.split(" ");
  vector<Computer> bufferFound;
  bool isUnique = true;

  if (searchString == "") {
    return computerRepository.getComputerList();
  }
  else if (list.at(0) == "??") {
    searchString.remove(QChar('?'));
    searchString.replace(QString("Built year"), QString(
                           "YearBuilt"), Qt::CaseInsensitive);
    return computerRepository.advancedSearchComputer(searchString);
  }
  else {
    // To search for each word indivudally and only return unique objects
    for (int i = 0; i < list.size(); i++) {
      vector<Computer> buffer = computerRepository.searchComputer(list.at(i));

      for (int j = 0; j < buffer.size(); j++) {
        for (int k = 0; k < bufferFound.size(); k++) {
          if ((buffer.at(j)).getId() == (bufferFound.at(k)).getId()) {
            isUnique = false;
          }
        }

        if (isUnique) {
          bufferFound.push_back(buffer.at(j));
        }
        isUnique = true;
      }
    }
    return bufferFound;
  }
}

vector<Scientist>Service::getAssociatedScientist(Computer computerDetails) {
  int idComputerToMatch = computerDetails.getId();

  return scientistRepository.getAssociatedScientists(idComputerToMatch);
}

vector<Computer>Service::getAssociatedComputers(Scientist scientistDetails) {
  int idScientistToMatch = scientistDetails.getId();

  return computerRepository.getAssociatedComputers(idScientistToMatch);
}

bool Service::createScientistToAdd(string name, string gender, int yearborn, int yeardied, string knownFor) {

  string buffer = "", bufferFirst = "", bufferLast = "";
  bool   bufferGender;

  vector<string> nameContainer;

  // To be able to seperate first and last name a sstream is created
  stringstream nameStream;
  nameStream.str(name);

  while (nameStream >> buffer) {
    nameContainer.push_back(buffer);
  }

  if (nameContainer.size() == 1) {
    bufferFirst = nameContainer.back();
  }
  else {
    for (unsigned int i = 0; i < nameContainer.size() - 1; i++) {
      bufferFirst += nameContainer.at(i);

      if (i < (nameContainer.size() - 2)) bufferFirst += " ";
    }
    bufferLast = nameContainer.back();
  }

  if ((gender == "f") || (gender == "F")) {
    bufferGender = true;
  }
  else {
    bufferGender = false;
  }


  Scientist newScientist(bufferFirst, bufferLast, bufferGender, yearborn, yeardied, knownFor);

  return scientistRepository.addToDatabase(newScientist);
}

bool Service::createComputerToAdd(string name, string type, bool built, int yearBuilt) {
  Computer newComputer(name, type, built, yearBuilt);

  return computerRepository.addToDatabase(newComputer);
}

bool Service::removeScientist(int idScientistToRemove) {
  return scientistRepository.removeScientist(idScientistToRemove);
}

bool Service::removeComputer(int idComputerToRemove) {
  return computerRepository.removeComputer(idComputerToRemove);
}

bool Service::createRelation(int idScientist, int idComputer) {
  return relationRepository.addRelation(idScientist, idComputer);
}

bool Service::removeRelation(int idScientist, int idComputer) {
  return relationRepository.removeRelation(idScientist, idComputer);
}

int Service::numberOfRelations() {
  return relationRepository.sizeOfTable();
}
