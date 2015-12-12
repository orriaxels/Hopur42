#ifndef INITDATABASECONNECT
#define INITDATABASECONNECT

#include <QtSql>
#include <QFileInfo>

//Creates static connection to database specified in set databasename
//Keeps an open connection to database while program is running
static bool createStaticConnection(){

  QFileInfo checkFile("ComputerHardware.sqlite");
  // check if file exists and if yes: Is it really a file and no directory?
  if (checkFile.exists() && checkFile.isFile()) {
    QSqlDatabase dataB = QSqlDatabase::addDatabase("QSQLITE");
    dataB.setDatabaseName("ComputerHardware.sqlite");
    dataB.open();

    if ( !dataB.open() ) {//since it creates file if db is not there this should not happen
      return false;
      }
    else{
      return true;
      }

  }
  else {
      return false;
  }
}
#endif // INITDATABASECONNECT
