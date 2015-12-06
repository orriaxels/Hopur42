#include <string>
#include <stdlib.h> //for atoi()
#include "util/inputcheck.h"
#include "ui/interface.h"

using namespace std;
Inputcheck::Inputcheck(){
//default
}

bool Inputcheck::isInputGood(int fromNumber, int toNumber, string& input){
  int compareTo =0;
  bool foundChar=false;

  //so it ignores all inputs with some chars
  for(int j=0; j< input.length(); j++){
      if( !( isdigit(input[j]) ) )
          foundChar=true;
  }
  if(! foundChar){
      compareTo= atoi(input.c_str() );
      for(int i=fromNumber; i<=toNumber; i++){
        if(compareTo==i){
          cin.ignore(1000, '\n');
          return true;
        }
      }

  }
  cin.clear();
  cin.ignore(1000, '\n');
  InterFace interfaceVar; //compiler does not let me create var in private...
  interfaceVar.invalidInput();
  return false;
}
