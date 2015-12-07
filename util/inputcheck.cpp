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

bool Inputcheck::isNameGood(string& name, string& illegal){
  if(name.empty()){
    return false;
  }else{
    for(unsigned int i = 0; i < name.length(); i++){ 
      if((islower(name[0])) || (islower(name[i]) && name[i-1] == ' ')){
        name[i] = toupper(name[i]);
      }
      else if(!isalpha(name[i])){
        if(name[i] == ' ' && name[i+1] == ' '){
          name.erase(name.begin()+i);
          i--;
        }else if(name[i] != ' ' ){
          illegal = name[i];
          return false;
        }else if( (i != 0) && (isupper(name[i]) && name[i-1] != ' ')){
                name[i] = tolower(name[i]);
        }
      }    
      
      return true;
   }    
  }
}

bool Inputcheck::cinFailCheck(int input){
  if(cin.fail()){
    cin.clear();
    cin.ignore(1000, '\n');
    return true;
  }else{
    return false;
  }
}  

bool Inputcheck::checkNumber(int year, int lowerNumber, int higerNumber){
  if(year < lowerNumber || year > higerNumber){
    return true;
  }else if(year > 2015){
    return true;
  }else{
    return false;
  }
}



