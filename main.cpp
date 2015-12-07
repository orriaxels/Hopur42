#include "ui/interface.h"
#include "util/initdatabaseconnect.h"

using namespace std;


int main(){
  
    if (!createConnection())
      return 1;

    InterFace ifDisp;
    ifDisp.runInterFace(); //opens the interface for user

    return 0;
}
