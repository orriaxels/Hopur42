#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include <QtSql>
#include <QString>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scientistRadioButton->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_scientistRadioButton_toggled(bool checked)
{
    model = new QSqlTableModel();

    ui->mainTable->setModel(model);

    model->setTable("Scientists");

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Born"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Died"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Known for"));
    model->select();

    ui->mainTable->hideColumn(0);
    ui->mainTable->hideColumn(7);
    ui->mainTable->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->mainTable->setColumnWidth(1,120);
    ui->mainTable->setColumnWidth(3,50);
    ui->mainTable->setColumnWidth(4,60);
    ui->mainTable->setColumnWidth(5,60);
    ui->mainTable->verticalHeader ()->hide();

}

void MainWindow::on_computerRadioButton_toggled(bool checked)
{
    model = new QSqlTableModel();
    ui->mainTable->setModel(model);
    model->setTable("Computers");

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Year built"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Was it built?"));
    model->select();

    ui->mainTable->hideColumn(0);
    ui->mainTable->hideColumn(5);
    ui->mainTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->mainTable->setColumnWidth(2,80);
    ui->mainTable->setColumnWidth(3,200);
    ui->mainTable->verticalHeader ()->hide();



}

void MainWindow::on_relationRadioButton_toggled(bool checked)
{


}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

}

void MainWindow::on_actionAbout_us_triggered()
{
    QString linkGroup="https://en.wikipedia.org/wiki/42_(number)";
    QMessageBox::information(this, tr("We rock!"), tr("<p>This project is work in porgess More information is on  <a href=\"https://github.com/orriaxels/Hopur42\" style=\"color:blue\">Github</a> </p> "
                                                      "<p>Group <a href=\"https://en.wikipedia.org/wiki/42_(number)\" style=\"color:blue\">Web page</a> </p>"));
}

void MainWindow::on_addScientist_triggered()
{
    addDialog add;
    add.setModal(true);
    add.exec();
}
