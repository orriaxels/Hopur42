#include "ui/mainwindow.h"
#include "repositories//initdatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  bool newDatabase=false;

  if (!createStaticConnection()) {
    newDatabase = true;
  }

  MainWindow window;
  window.setWindowTitle("Hopur 42");
  if(newDatabase){
	  window.databaseFailedOpen();
	  return 0;
  }
  window.show();

  return a.exec();
}
