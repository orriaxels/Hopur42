#ifndef INITDATABASECONNECT
#define INITDATABASECONNECT

#include <QtSql>

//Creates static connection to database specified in set databasename
//Keeps an open connection to database while program is running
static bool createStaticConnection()
{
  QSqlDatabase dataB = QSqlDatabase::addDatabase("QSQLITE");
  dataB.setDatabaseName("ComputerHardware.sqlite");
	dataB.open();

  if ( !dataB.open() ) //since it creates file if db is not there this should not happen
		return false;
  else
    return true;
}
#endif // INITDATABASECONNECT
