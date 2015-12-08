#include <iostream>
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
  for(unsigned int j=0; j< input.length(); j++){
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
                  }

              }else if( (i != 0) && (isupper(name[i]) && name[i-1] != ' ')){
                  name[i] = tolower(name[i]);
              }
          }
        return true;
      }
  }
void Inputcheck::cinFailCheck(){
    cin.clear();
    cin.ignore(1000, '\n');
    InterFace interfaceVar;
    interfaceVar.invalidInput();
}

bool Inputcheck::checkNumber(int year, int lowerNumber, int higerNumber){
  InterFace interfaceVar;

  if(cin.fail()){
    cinFailCheck();
    return false;
  }else if(year < lowerNumber || year > higerNumber){
    cinFailCheck();
    return false;
  }else if(year > 2015){
    cinFailCheck();
    return false;
  }
  else{
    return true;
  }
}

bool Inputcheck::checkDyear(int year, int lowerNumber, int higerNumber){
  InterFace interfaceVar;

  if(cin.fail()){
    cinFailCheck();
    return false;
  }else if(year == 0){
    return true;  
  }else if(year < lowerNumber || year > higerNumber){
    cinFailCheck();
    return false;
  }else if(year > 2015){
    cinFailCheck();
    return false;
  }
  else{
    return true;
  }
}