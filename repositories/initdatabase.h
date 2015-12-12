#ifndef INITDATABASECONNECT
#define INITDATABASECONNECT

#include <QtSql>
#include <QFileInfo>

/* @breif Function starst a static connection to set database
 * @return returns true if connection sucsessful and
 * @return false if file does not exists or opening database fails  */
static bool createStaticConnection(){

    QFileInfo checkFile("ComputerHardware.sqlite");

    if (checkFile.exists() && checkFile.isFile()) {
        QSqlDatabase dataB = QSqlDatabase::addDatabase("QSQLITE");
        dataB.setDatabaseName("ComputerHardware.sqlite");
        dataB.open();

        if ( !dataB.open() ) {
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
