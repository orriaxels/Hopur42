#include "ui/mainwindow.h"
#include "repo/initdatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createStaticConnection();

    MainWindow w;
    w.show();

    return a.exec();
}
