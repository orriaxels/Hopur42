#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "services/service.h"
#include "models/computer.h"
#include "models/scientist.h"
#include "adddialog.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>

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
    vector<Scientist> allScientists=services.getSortedScientistList();
    intilizeScientistTable();
    displayScientistList(allScientists);

}


void MainWindow::intilizeScientistTable(){

    ui->mainTable->verticalHeader()->setVisible(false);

    ui->mainTable->setColumnCount(6);
    ui->mainTable->setColumnWidth(0,120);
    ui->mainTable->setColumnWidth(1,100);
    ui->mainTable->setColumnWidth(2,80);
    ui->mainTable->setColumnWidth(3,80);
    ui->mainTable->setColumnWidth(4,80);

    QStringList columns;
    columns<<"First name"<< "Last name"<< "Gender"<< "Born"<<"Died"<< "Known for";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    ui->mainTable->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    ui->mainTable->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(5)->setTextAlignment(Qt::AlignLeft);

    ui->mainTable->sortByColumn(0,Qt::AscendingOrder);
}

void MainWindow::displayScientistList(std::vector<Scientist> listToDisplay){

    ui->mainTable->clearContents();
    ui->mainTable->setRowCount(listToDisplay.size());

    for (unsigned int i = 0; i < listToDisplay.size(); i++) {
        QString fName = QString::fromStdString( ((listToDisplay.at(i)).getF()) );
        QString lName = QString::fromStdString( ((listToDisplay.at(i)).getL()) );
        QString gender = QString::number( (listToDisplay.at(i)).getGender());
        QString born = QString::number((listToDisplay.at(i)).getYearBorn());
        QString died = QString::number((listToDisplay.at(i)).getYearDied());
        QString known = QString::fromStdString( ((listToDisplay.at(i)).getKnownFor()) );

        ui->mainTable->setItem(i, 0, new QTableWidgetItem(fName));
        ui->mainTable->setItem(i, 1, new QTableWidgetItem(lName));
        ui->mainTable->setItem(i, 2, new QTableWidgetItem(gender));
        ui->mainTable->setItem(i, 3, new QTableWidgetItem(born));
        ui->mainTable->setItem(i, 4, new QTableWidgetItem(died));
        ui->mainTable->setItem(i, 5, new QTableWidgetItem(known));
    }
}

void MainWindow::on_computerRadioButton_toggled(bool checked)
{
    vector<Computer> allComputers=services.getSortedComputerList();
    intilizeComputerTable();
    displayComputerList(allComputers);
}

void MainWindow::intilizeComputerTable(){

    ui->mainTable->verticalHeader()->setVisible(false);
    ui->mainTable->setColumnCount(4);
    ui->mainTable->setColumnWidth(0,200);
    ui->mainTable->setColumnWidth(1,200);
    ui->mainTable->setColumnWidth(2,200);

    QStringList columns;
    columns<<"Name"<< "Type"<< "Built"<< "Built year";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->sortByColumn(0,Qt::AscendingOrder);
    ui->mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mainTable->setSelectionMode(QAbstractItemView::SingleSelection);



}

void MainWindow::displayComputerList(std::vector<Computer> listToDisplay){
    ui->mainTable->clearContents();
    ui->mainTable->setRowCount( listToDisplay.size() );

    for (unsigned int i = 0; i < listToDisplay.size(); i++)
    {
        QString name = QString::fromStdString( ((listToDisplay.at(i)).getName()) ); //bindvalue needs QString
        QString type = QString::fromStdString( ((listToDisplay.at(i)).getType() ) ); //bindvalue needs QString
        QString built = QString::number ( (listToDisplay.at(i)).getBuild() );
        QString builtYear = QString::number((listToDisplay.at(i)).getBuildYear());

        ui->mainTable->setItem(i, 0, new QTableWidgetItem(name));
        ui->mainTable->setItem(i, 1, new QTableWidgetItem(type));
        ui->mainTable->setItem(i, 2, new QTableWidgetItem(built));
        ui->mainTable->setItem(i, 3, new QTableWidgetItem(builtYear));
    }

}



void MainWindow::on_relationRadioButton_toggled(bool checked)
{

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1){

    if( ui->scientistRadioButton->isChecked() ){
        ui->mainTable->setSortingEnabled(false);
        displayScientistList( services.searchScientists( arg1 ) );
        ui->mainTable->setSortingEnabled(true);
    }
    else if (ui->computerRadioButton->isChecked()){
        ui->mainTable->setSortingEnabled(false);
        displayComputerList( services.searchComputers( arg1 ) );
        ui->mainTable->setSortingEnabled(true);
    }
    else if (ui->relationRadioButton->isChecked()) {

    }
}


void MainWindow::on_actionAbout_us_triggered()
{
    QString linkGroup="https://en.wikipedia.org/wiki/42_(number)";
    QMessageBox::information(this, tr("About us"), tr("<p>This project is work in progess </p>"
                                                      "<p>More information is on  <a href=\"https://github.com/orriaxels/Hopur42\" style=\"color:blue\">Github</a> </p> "
                                                      "<p>Group <a href=\"https://en.wikipedia.org/wiki/42_(number)\" style=\"color:blue\">Web page</a> </p>"));
}

void MainWindow::on_addScientist_triggered()
{
    AddDialog add;
    add.setModal(true);
    add.exec();
}

void MainWindow::databaseFailedOpen(){
  QMessageBox::critical(this, tr("Database fail!"), tr("The program was not able to open the database. <p> Check if database exists or path of database.</p>"));
}




void MainWindow::on_buttunAdd_clicked()
{
    AddDialog add;
    add.setModal(true);
    add.exec();
}

void MainWindow::on_buttunRemove_clicked()
{
    QMessageBox msgBox;

    msgBox.setText("Information about the selected entry");
    msgBox.setInformativeText("Do you want to remove your selection?");
    msgBox.addButton(tr("Save"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancel"), QMessageBox::NoRole);


    msgBox.exec();
}
