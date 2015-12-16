#include "addcompdialog.h"
#include "ui_addcompdialog.h"
#include "models/computer.h"
#include "services/service.h"

#include <QMessageBox>
#include <QLayout>
#include <QTime>
#include <string>

using namespace std;

AddCompDialog::AddCompDialog(int id, QWidget *parent) :QDialog(parent),
    ui(new Ui::AddCompDialog) {

    ui->setupUi(this);
    idOfComputer = id;

    ui->radioYes->setChecked(true);
    ui->builtYearSpinBox->setMinimum(1000);
    ui->builtYearSpinBox->setMaximum(QDate::currentDate().year());

    if (idOfComputer == 0) {
       setUpForAdd();
    }
    else {
       setUpForEdit();
    }
}

AddCompDialog::~AddCompDialog() {
    delete ui;
}

void AddCompDialog::setUpForAdd() {
    ui->buttonAdd->setText("Add");
    ui->builtYearSpinBox->setValue(1900);
}

void AddCompDialog::setUpForEdit() {
    ui->buttonAdd->setText("Edit");
    QString computerQuery = QString::number(idOfComputer);
    editComputer = (services.searchComputers("?? id=" + computerQuery)).at(0);

    QString name       = QString::fromStdString((editComputer.getName()));
    int     builtY     = editComputer.getBuildYear();
    QString type       = QString::fromStdString((editComputer.getType()));
    bool    builtOrNot = editComputer.getBuild();

    ui->lineEditName->setText(name);
    ui->builtYearSpinBox->setValue(builtY);

    if (builtOrNot) {
        ui->radioYes->setChecked(true);
    }
    else {
        ui->radioNo->setChecked(true);
        ui->builtYearSpinBox->setEnabled(false);
    }

    if (type == "Mechanical") {
        ui->comboType->setCurrentIndex(1);
    }
    else if (type == "Electronic") {
        ui->comboType->setCurrentIndex(2);
    }
    else if (type == "Electro-Mechanical") {
        ui->comboType->setCurrentIndex(3);
    }
    else if (type == "Transistorized") {
        ui->comboType->setCurrentIndex(4);
    }
    else {
        ui->comboType->setCurrentIndex(0);
    }
}

void AddCompDialog::on_buttonAdd_clicked() {
    QString computerName = ui->lineEditName->text().simplified();

    if (computerName== "") {
        QMessageBox::warning(0, "Error", "Name field is empty");
    }
    else if (ui->comboType->currentIndex()  == 0) {
        QMessageBox::warning(0, "Error", "Choose computer type");
    }
    else {
    	if (idOfComputer == 0) {
    	    confirmNew();
    	}
    	else {
    	    confirmEdit();
    	}
    }
}

void AddCompDialog::confirmNew() {
    QString type         = ui->comboType->currentText(),
            computerName = ui->lineEditName->text().simplified(),
            builtString, confirmationText, newComputer;
    bool built = ui->radioYes->isChecked();
    int  yearBuilt;

    if (built) {
        yearBuilt   = ui->builtYearSpinBox->value();
        builtString = "Yes.";
    }
    else {
        yearBuilt   = 0;
        builtString = "Nope.";
    }
    newComputer = "Name: " + computerName + "\nType: " + type +
                      "\nWas it built: " + builtString + "\n";

    if (built) {
        newComputer += "When: " + QString::number(yearBuilt) + "\n\n";
    }
    confirmationText=newComputer+" Are you sure you want to add"
                                     " this to the database ?";

    QMessageBox addComputerConfirm;
    addComputerConfirm.setText(confirmationText);
    addComputerConfirm.setWindowTitle("Confirm");
    QAbstractButton *pButtonYes = addComputerConfirm.addButton(tr("Yes"), QMessageBox::YesRole);
    addComputerConfirm.addButton(tr("No"), QMessageBox::NoRole);
    addComputerConfirm.exec();


    if (addComputerConfirm.clickedButton() == pButtonYes) {
    	if (services.createComputerToAdd(computerName.toStdString(),
    	                                 type.toStdString(), built, yearBuilt)) {

    	    QMessageBox::information(0, "Added to database", "Entry sucsessfully added into database");
    	    on_buttonReset_clicked();
    	}
    	else {
    	    QMessageBox::warning(0, "Error", "Error! \n\nUnable to add to database");
    	}
    }
}

void AddCompDialog::confirmEdit() {
    QString type         = ui->comboType->currentText().simplified(),
            computerName = ui->lineEditName->text().simplified(),
            builtString, confirmationText, oldComputer, updatedComptuer;
    bool built = ui->radioYes->isChecked();
    int  yearBuilt;

    if (built) {
        yearBuilt   = ui->builtYearSpinBox->value();
        builtString = "Yes.";
    }
    else {
        yearBuilt   = 0;
        builtString = "Nope.";
    }
    updatedComptuer = "Name: " + computerName + "\nType: " + type +
                      "\nWas it built: " + builtString + "\n";

    if (built) {
        updatedComptuer += "When: " + QString::number(yearBuilt) + "\n";
    }


    oldComputer = "Name: " + QString::fromStdString(editComputer.getName())
                  + "\nType: " + QString::fromStdString(editComputer.getType())
                  + "\nWas it built: ";

    if (editComputer.getBuild()) {
        oldComputer += "Yes.\nWhen: " + QString::number(editComputer.getBuildYear()) + "\n\n";
    }
    else {
	       oldComputer += "Nope.\n\n";
    }

    confirmationText = QString(
        "Confirm change from:\n\n" + oldComputer + "To:\n" + updatedComptuer +
        "\nAre you sure you want to update?");


    QMessageBox addComputerConfirm;
    addComputerConfirm.setText(confirmationText);
    addComputerConfirm.setWindowTitle("Confirm");
    QAbstractButton *pButtonYes = addComputerConfirm.addButton(tr("Yes"), QMessageBox::YesRole);
    addComputerConfirm.addButton(tr("No"), QMessageBox::NoRole);
    addComputerConfirm.exec();

    if (addComputerConfirm.clickedButton() == pButtonYes) {
    	Computer updatedComputer(idOfComputer, computerName.toStdString(),
    	                         type.toStdString(), built, yearBuilt);

    	if (services.updateComputer(updatedComputer)) {
    	    QMessageBox::information(0, "Added to database",
    	                             "Entry sucsessfully updated");
    	    on_buttonReset_clicked();
    	}
    	else {
    	    QMessageBox::warning(0, "Error", "Error! \n\nUnable to add to database");
    	}
    }
    this->close();
}

void AddCompDialog::on_radioYes_clicked() {
    ui->builtYearSpinBox->setEnabled(true);
}

void AddCompDialog::on_radioNo_clicked() {
    ui->builtYearSpinBox->setEnabled(false);
}

void AddCompDialog::on_buttonReset_clicked() {
    ui->lineEditName->clear();
    ui->radioYes->setChecked(true);
    ui->radioNo->setChecked(false);
    ui->builtYearSpinBox->setEnabled(true);
    ui->builtYearSpinBox->setValue(1900);
    ui->comboType->setCurrentIndex(0);
}
