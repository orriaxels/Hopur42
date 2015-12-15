#ifndef INITDATABASECONNECT
#define INITDATABASECONNECT

#include <QtSql>
#include <QFileInfo>

/* @breif Function starst a static connection to set database
 * @return returns true if connection sucsessful and
 * @return false if file does not exists */
static bool createStaticConnection(){

    QFileInfo checkFile("ComputerHardware.sqlite");

    if (checkFile.exists() && checkFile.isFile()) {

		QSqlDatabase dataB = QSqlDatabase::addDatabase("QSQLITE");
		dataB.setDatabaseName("ComputerHardware.sqlite");
		dataB.open();
        return true;
    }

    return false;
}
#endif // INITDATABASECONNECT
