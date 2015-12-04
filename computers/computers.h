#include <iostream>
#include <string>
#endif // COMPUTERS_H

using namespace std;

class Computer
{
    public:
        Computers();
        Computers(string cName, string cType, bool build, int bldYear);

        string getName();
        string getType();
        bool getBuild();
        int getBuildYear();

        void setName(const string computerName);
        void setType(const string computerType);
        void setBuild(const bool build);
        void setBuildYear(const int buildYear);

    private:
        string computername;  // Name of the computer
        string computertype;  // Type of the computer
        bool ifBuild;  // True for build, false for not build
        int buildyear;  // The year the computer was build
};
