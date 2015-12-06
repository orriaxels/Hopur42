#ifndef INPUTCHECK_H
#define INPUTCHECK_H
#include <string>
using namespace std;
class Inputcheck
{
    public:
      Inputcheck();
      bool isInputGood(int fromNumber, int toNumber, string& input) ;
	  bool isNameGood(string& name, string& illegal);
	  bool isStringEmpty(string text);	    
    private:
};

#endif // INPUTCHECK_H
