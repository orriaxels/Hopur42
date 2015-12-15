#include <string>
#include "computer.h"

using namespace std;

Computer::Computer() {
    computerName = "";
    computerType = "";
    ifBuilt      = 0;
    builtYear    = 0;
}

Computer::Computer(string computeName, string computeType, bool built, int buitYear) {
    computerName = computeName;
    computerType = computeType;
    ifBuilt      = built;
    builtYear    = buitYear;
}

Computer::Computer(int tableId, string computeName, string computeType, bool built, int buitYear) {
    compId       = tableId;
    computerName = computeName;
    computerType = computeType;
    ifBuilt      = built;
    builtYear    = buitYear;
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
