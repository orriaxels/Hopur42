#ifndef computers_h
#define computers_h

#include <iostream>
#include <string>

using namespace std;

class Computers
{
    public:
        Computers();
        Computers(string cName, string cType, bool build, int bldYear);
        Computers(int tableId, string cName, string cType, bool build, int bldYear);


        int getId() const;
        string getName() const;
        string getType() const;
        bool getBuild() const;
        int getBuildYear() const;

    private:
        int compId;
        string computername;  // Name of the computer
        string computertype;  // Type of the computer
        bool ifBuild;  // True for build, false for not build
        int buildyear;  // The year the computer was build
};

#endif // COMPUTERS_H
