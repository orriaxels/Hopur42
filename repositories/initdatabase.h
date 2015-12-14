#ifndef INITDATABASECONNECT
#define INITDATABASECONNECT

#include <QtSql>
#include <QFileInfo>

/* @breif Function starst a static connection to set database
 * @return returns true if connection sucsessful and
 * @return false if file does not exists or opening database fails  */
static bool createStaticConnection(){

    QFileInfo checkFile("/Users/Shoshan/Documents/school/hopur42/build-Tableview2-Desktop_Qt_5_5_1_clang_64bit-Debug/ComputerHardware.sqlite");

    if (checkFile.exists() && checkFile.isFile()) {
        QSqlDatabase dataB = QSqlDatabase::addDatabase("QSQLITE");
        dataB.setDatabaseName("/Users/Shoshan/Documents/school/hopur42/build-Tableview2-Desktop_Qt_5_5_1_clang_64bit-Debug/ComputerHardware.sqlite");
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
