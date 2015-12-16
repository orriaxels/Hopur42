#ifndef computer_h
#define computer_h

#include <string>
using namespace std;

class Computer
{
public:
        //Available constructors
        Computer();
        Computer(string computeName, string computeType, bool built, int buitYear);
        Computer(int tableId, string computeName, string computeType, bool built, int buitYear);

        //Returns value of the private variables.
        int getId() const;
        string getName() const;
        string getType() const;
        bool getBuild() const;
        int getBuildYear() const;

private:
        int compId;           // Primary key id of computer from table in DB
        string computerName;  // Name of the computer
        string computerType;  // Type of the computer
        bool ifBuilt;         // True for build, false for not build
        int builtYear;        // The year the computer was build
};

#endif // COMPUTER_H
