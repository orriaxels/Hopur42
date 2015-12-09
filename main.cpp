#include "ui/interface.h"
#include "repo/initdatabase.h"

int main(){

    if (!createStaticConnection())
      return 1;

    InterFace ifDisp;
    ifDisp.runInterFace(); //opens the main interface

    return 0;
}
