#include "ui/mainwindow.h"
#include "repositories//initdatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createStaticConnection();

    MainWindow w;
    w.show();

    return a.exec();
}
