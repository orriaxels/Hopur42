#include "addrelationdialog.h"
#include "ui_addrelationdialog.h"

#include <QString>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>

AddRelationDialog::AddRelationDialog(QWidget *parent) :QDialog(parent),
    ui(new Ui::AddRelationDialog){

    ui->setupUi(this);

    intilizeTables();
    displayScientistList(services.getSortedScientistList());
    displayCompterList(services.getSortedComputerList());

    idComputer=0;
    idScientist=0;
    nameScientist="*Scientist*";
    nameComputer="*Computer*";
    ui->lableTobeGrouped->setText( "Create relation between " +nameScientist +
                                                      " and " +nameComputer);
    ui->buttonAdd->setEnabled(false);
}

AddRelationDialog::~AddRelationDialog(){
    delete ui;
}

void AddRelationDialog::intilizeTables(){

    ui->tableScientists->setColumnCount(2);
    ui->tableScientists->setColumnWidth(0,0);

    ui->tableComputers->setColumnCount(2);
    ui->tableComputers->setColumnWidth(0,0);
}

void AddRelationDialog::displayScientistList(vector<Scientist> listToDisplay){
    ui->tableScientists->clear();
    ui->tableScientists->setRowCount(listToDisplay.size());

    for (unsigned int row = 0; row < listToDisplay.size(); row++) {

        QString idScientist = QString::number( (listToDisplay.at(row)).getId() );
        QString name = QString::fromStdString( (listToDisplay.at(row)).getF() );
                name+= +" "+ QString::fromStdString( (listToDisplay.at(row)).getL() );

        ui->tableScientists->setItem(row, 0, new QTableWidgetItem(idScientist));
        ui->tableScientists->setItem(row, 1, new QTableWidgetItem(name));
    }
    ui->tableScientists->selectRow(0);
}

void AddRelationDialog::displayCompterList(vector<Computer> listToDisplay){
    ui->tableComputers->clear();
    ui->tableComputers->setRowCount(listToDisplay.size());

    for (unsigned int row = 0; row < listToDisplay.size(); row++) {
        QString idComputer = QString::number( (listToDisplay.at(row)).getId() );
        QString name = QString::fromStdString( (listToDisplay.at(row)).getName() );

        ui->tableComputers->setItem(row, 0, new QTableWidgetItem(idComputer));
        ui->tableComputers->setItem(row, 1, new QTableWidgetItem(name));
    }
    ui->tableComputers->selectRow(0);
}

void AddRelationDialog::on_lineEditScientistFilter_textChanged(const QString &arg1){
    displayScientistList( services.searchScientists(arg1 ) );
}

void AddRelationDialog::on_lineEditComputerFilter_textChanged(const QString &arg1){
    displayCompterList(services.searchComputers(arg1));
}

void AddRelationDialog::on_tableScientists_doubleClicked(const QModelIndex &index){
    int indexRow=ui->tableScientists->currentRow();
    idScientist =ui->tableScientists->item(indexRow, 0)->text().toUInt();
    nameScientist =ui->tableScientists->item(indexRow, 1)->text();
    previewRelationDisplay();

}

void AddRelationDialog::on_tableComputers_doubleClicked(const QModelIndex &index){
    int indexRow=ui->tableComputers->currentRow();
    idComputer =ui->tableComputers->item(indexRow, 0)->text().toUInt();
    nameComputer =ui->tableComputers->item(indexRow, 1)->text();
    previewRelationDisplay();
}

void AddRelationDialog::previewRelationDisplay(){

    ui->lableTobeGrouped->setText( "Create relation between " +nameScientist +
                                                      " and " +nameComputer);

    if(idScientist !=0 && idComputer != 0){
        ui->buttonAdd->setEnabled(true);
    }
}

void AddRelationDialog::on_buttonAdd_clicked(){
    if( services.createRelation(idScientist, idComputer) ){
      QMessageBox::information(0, "Added to database", "Relation between " +nameScientist +
                                " and "+nameComputer + "has been added to the database.");
      on_buttonClear_clicked();
    }
    else{
      QMessageBox::warning(0, "Error",
                           "Error! \n\nUnable to add to database");
    }
}

void AddRelationDialog::on_buttonClear_clicked(){
    idComputer=0;
    idScientist=0;
    nameScientist="*Scientist*";
    nameComputer="*Computer*";
    ui->lableTobeGrouped->setText( "Create relation between " +nameScientist +
                                                      " and " +nameComputer);
    ui->lineEditComputerFilter->clear();
    ui->lineEditScientistFilter->clear();
    ui->buttonAdd->setEnabled(false);
}
