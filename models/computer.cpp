#include <string>
#include "computer.h"

using namespace std;

Computer::Computer() {
  computerName = "";
  computerType = "";
  ifBuilt      = 0;
  builtYear    = 0;
}

Computer::Computer(string cName, string cType, bool built, int bltYear) {
  computerName = cName;
  computerType = cType;
  ifBuilt      = built;
  builtYear    = bltYear;
}

Computer::Computer(int tableId, string cName, string cType, bool built, int bltYear) {
  compId       = tableId;
  computerName = cName;
  computerType = cType;
  ifBuilt      = built;
  builtYear    = bltYear;
}

// Get functions
int Computer::getId() const {
  return compId;
}

string Computer::getName() const {
  return computerName;
}

string Computer::getType() const {
  return computerType;
}

bool Computer::getBuild() const {
  return ifBuilt;
}

int Computer::getBuildYear() const {
  return builtYear;
}
