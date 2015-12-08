#ifndef computers_h
#define computers_h

#include <vector>
#include <string>

using namespace std;

class Computers
{
    public:
        Computers();
        Computers(string cName, string cType, bool build, int bldYear);
        Computers(int tableId, string cName, string cType, bool build, int bldYear);

        //Get private variables of Computer
        int getId() const;
        string getName() const;
        string getType() const;
        bool getBuild() const;
        int getBuildYear() const;

        //Creates connections in junction table
        bool setConnectWithPers(const vector<int> persId);

    private:
        int compId;           //Store PK of computer from table in DB
        string computername;  // Name of the computer
        string computertype;  // Type of the computer
        bool ifBuild;         // True for build, false for not build
        int buildyear;        // The year the computer was build
        vector<int> junctionWithPers; //Id of Persons this computer is junctioned with
};

#endif // COMPUTERS_H
