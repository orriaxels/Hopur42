#ifndef INITDATABASECONNECT
#define INITDATABASECONNECT

#include <QtSql>

static bool createConnection()
{
  QSqlDatabase datab = QSqlDatabase::addDatabase("QSQLITE");
  datab.setDatabaseName("ComputerHardware.sqlite");
	datab.open();

  if ( !datab.open() ) {
    cout<< "Unable to connecto to database"<<endl<<endl;
		return false;
	}

    return true;
}

#endif // INITDATABASECONNECT
