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

    ui->mainTable->setColumnCount(7);
    ui->mainTable->setColumnWidth(0,0);
    ui->mainTable->setColumnWidth(1,120);
    ui->mainTable->setColumnWidth(2,100);
    ui->mainTable->setColumnWidth(3,80);
    ui->mainTable->setColumnWidth(4,80);
    ui->mainTable->setColumnWidth(5,80);

    QStringList columns;
    columns<<"id"<<"First name"<< "Last name"<< "Gender"<< "Born"<<"Died"<< "Known for";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    ui->mainTable->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignLeft);
    ui->mainTable->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(5)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(6)->setTextAlignment(Qt::AlignLeft);

    ui->mainTable->sortByColumn(1,Qt::AscendingOrder);
}

void MainWindow::displayScientistList(std::vector<Scientist> listToDisplay){

    scientistsInTable=listToDisplay;

    ui->mainTable->clearContents();
    ui->mainTable->setRowCount(listToDisplay.size());
    ui->mainTable->setSortingEnabled(false);

    for (unsigned int i = 0; i < listToDisplay.size(); i++) {
        QString id = QString::number( ((listToDisplay.at(i)).getId()) );
        QString fName = QString::fromStdString( ((listToDisplay.at(i)).getF()) );
        QString lName = QString::fromStdString( ((listToDisplay.at(i)).getL()) );
        QString gender = QString::number( (listToDisplay.at(i)).getGender());
        QString born = QString::number((listToDisplay.at(i)).getYearBorn());
        QString died = QString::number((listToDisplay.at(i)).getYearDied());
        QString known = QString::fromStdString( ((listToDisplay.at(i)).getKnownFor()) );

        ui->mainTable->setItem(i, 0, new QTableWidgetItem(id));
        ui->mainTable->setItem(i, 1, new QTableWidgetItem(fName));
        ui->mainTable->setItem(i, 2, new QTableWidgetItem(lName));
        ui->mainTable->setItem(i, 3, new QTableWidgetItem(gender));
        ui->mainTable->setItem(i, 4, new QTableWidgetItem(born));
        ui->mainTable->setItem(i, 5, new QTableWidgetItem(died));
        ui->mainTable->setItem(i, 6, new QTableWidgetItem(known));

    }
	ui->mainTable->setSortingEnabled(true);
}

void MainWindow::on_computerRadioButton_toggled(bool checked)
{
    vector<Computer> allComputers=services.getSortedComputerList();
    intilizeComputerTable();
    displayComputerList(allComputers);
}

void MainWindow::intilizeComputerTable(){

    ui->mainTable->verticalHeader()->setVisible(false);
    ui->mainTable->setColumnCount(5);
    ui->mainTable->setColumnWidth(0,0);
    ui->mainTable->setColumnWidth(1,200);
    ui->mainTable->setColumnWidth(2,200);
    ui->mainTable->setColumnWidth(3,200);

    QStringList columns;
    columns<<"id"<<"Name"<< "Type"<< "Built"<< "Built year";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->sortByColumn(1,Qt::AscendingOrder);
    ui->mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mainTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::displayComputerList(std::vector<Computer> listToDisplay){
    ui->mainTable->clearContents();
	ui->mainTable->setSortingEnabled(false);
    ui->mainTable->setRowCount( listToDisplay.size() );

    for (unsigned int i = 0; i < listToDisplay.size(); i++)
    {
        QString id = QString::number( ((listToDisplay.at(i)).getId()) );
        QString name = QString::fromStdString( ((listToDisplay.at(i)).getName()) );
        QString type = QString::fromStdString( ((listToDisplay.at(i)).getType() ) );
        QString built = QString::number ( (listToDisplay.at(i)).getBuild() );
        QString builtYear = QString::number((listToDisplay.at(i)).getBuildYear());

        ui->mainTable->setItem(i, 0, new QTableWidgetItem(id));
        ui->mainTable->setItem(i, 1, new QTableWidgetItem(name));
        ui->mainTable->setItem(i, 2, new QTableWidgetItem(type));
        ui->mainTable->setItem(i, 3, new QTableWidgetItem(built));
        ui->mainTable->setItem(i, 4, new QTableWidgetItem(builtYear));
    }
	ui->mainTable->setSortingEnabled(true);
}

void MainWindow::on_relationRadioButton_toggled(bool checked){
	intilizeRelationTable();
	displayRelationTable();
	if(checked){
        ui->lineEdit->clear();
		ui->lineEdit->setEnabled(false);
	}
	else{
		ui->lineEdit->setEnabled(true);
	}
}

void MainWindow::intilizeRelationTable(){

    ui->mainTable->verticalHeader()->setVisible(false);
    ui->mainTable->setColumnCount(2);
    ui->mainTable->setColumnWidth(0,300);

    QStringList columns;
    columns<<"Scientists name"<< "Computer name";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->sortByColumn(0,Qt::AscendingOrder);
    ui->mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mainTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::displayRelationTable(){
	  ui->mainTable->clearContents();
	  ui->mainTable->setSortingEnabled(false);
	  vector<Scientist> scientistsSorted= services.getSortedScientistList();
	  vector<Computer> bufferComputerList;
      int rowCount=0;
      ui->mainTable->setRowCount( 14 );

	  for(unsigned int i=0; i< scientistsSorted.size(); i++){
	    bufferComputerList= services.getAssociatedComputers(scientistsSorted.at(i));
	    if(bufferComputerList.size() >0 ){
	      for(unsigned int j=0; j<bufferComputerList.size(); j++){

			  QString nameScientist = QString::fromStdString( (scientistsSorted.at(i)).getF() );
			  nameScientist+= " "+ QString::fromStdString( (scientistsSorted.at(i)).getL() );
			  QString nameComputer = QString::fromStdString( (bufferComputerList.at(j)).getName() );

	          ui->mainTable->setItem(rowCount, 0, new QTableWidgetItem(nameScientist));
	          ui->mainTable->setItem(rowCount, 1, new QTableWidgetItem(nameComputer));
              rowCount++;
	      }
		}
	  }
	  ui->mainTable->setSortingEnabled(true);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1){

    if( ui->scientistRadioButton->isChecked() ){
        displayScientistList( services.searchScientists( arg1 ) );
    }
    else if (ui->computerRadioButton->isChecked()){
        displayComputerList( services.searchComputers( arg1 ) );
    }
}


void MainWindow::on_actionAbout_us_triggered()
{
    QMessageBox::information(this, tr("About us"),
                             tr("<p>This program lets you view and edit small databases of scientists and computers.</p>"
                              "<p>More information is on  <a href=\"https://github.com/orriaxels/Hopur42\" style=\"color:blue\">Github</a> </p> "
                              "<p>Group <a href=\"https://www.youtube.com/watch?v=dQw4w9WgXcQ\" style=\"color:blue\">Web page</a> </p>"));
}

void MainWindow::on_addScientist_triggered()
{
    AddDialog add;
    add.setModal(true);
    add.exec();
}

void MainWindow::databaseFailedOpen(){
  QMessageBox::critical(this, tr("Database fail!"),
                        tr("The program was not able to open the database. <p> Check if database exists or path of database.</p>"));
}

void MainWindow::on_buttunAdd_clicked()
{
    AddDialog add;
    add.setModal(true);
    add.exec();
}

void MainWindow::on_buttunRemove_clicked()
{
    int indexRow=ui->mainTable->currentRow();
    QString name=ui->mainTable->item(indexRow, 1)->text();
    QString lastName=ui->mainTable->item(indexRow, 2)->text();
    int id=ui->mainTable->item(indexRow, 0)->text().toUInt();

    QMessageBox confirmRemove;
    confirmRemove.setStandardButtons(QMessageBox::Yes);
    confirmRemove.addButton(QMessageBox::No);
    confirmRemove.setDefaultButton(QMessageBox::No);
    confirmRemove.setWindowTitle(tr("Are you sure?"));

    if( ui->scientistRadioButton->isChecked() ){
        confirmRemove.setText(("<p>You are about remove "
                                "<b>"+name+" "+lastName+ "</b> from the database.</p>"
                                "Are you sure you want to proceed?"));

        if(confirmRemove.exec() == QMessageBox::Yes){
            if(services.removeScientist(id)){
                ui->statusBar->showMessage("Succsessfully removed "+name+" "+lastName+" from the database.", 3000);
            }
        }
    }
    else if (ui->computerRadioButton->isChecked()){
        confirmRemove.setText(("<p>You are about remove "
                                "<b>"+name+" </b> from the database.</p>"
                                "Are you sure you want to proceed?"));

        if(confirmRemove.exec() == QMessageBox::Yes){
            if(services.removeComputer(id)){
                ui->statusBar->showMessage("Succsessfully removed "+name+" from the database.", 3000);
            }
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this, tr("How to filter"),
                             tr("<p>Type in text box to filter results."
                           "ie. \"ada enigma\" will return: Ada Lovelace and Alan Turing.</p>"
                           "<p>Type \"??\" at start of query for advances queries."
                           " These queries append after \"WHERE\" statement for current table.<br>"
                           "ie. \"Born > '1900' OR First name =\"bill\" will return all those "
                           "born after 1900 and all with first name Bill.</p>"
                           "<p>See <a href=\"https://www.sqlite.org/syntax/expr.html\" "
                           "style=\"color:blue\">SQLite documentation</a> for more info.</p> "));

}
