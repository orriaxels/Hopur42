#include "ui/mainwindow.h"
#include "repositories//initdatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if( createStaticConnection() ){
      w.show();
    }
    else{
      w.databaseFailedOpen();
      return 0;
    }

    return a.exec();
}
