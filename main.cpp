#include "ui/interface.h"
#include "util/initdatabaseconnect.h"

int main(){

    if (!createStaticConnection())
      return 1;

    InterFace ifDisp;
    ifDisp.runInterFace(); //opens the main interface

    return 0;
}
