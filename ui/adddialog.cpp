#include "adddialog.h"
#include "ui_adddialog.h"
#include "services/service.h"
#include "models/scientist.h"

#include <QMessageBox>
#include <QLayout>
#include <QTime>
#include <string>
#include <QPixmap>
#include <vector>

using namespace std;

AddDialog::AddDialog(int idScientistToEdit, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddDialog){

  ui->setupUi(this);
  idScientist=idScientistToEdit;

  QImage checkOk, checkNo;
  checkOk.load(":/icon/img/Ok-icon.png");
  checkNo.load(":/icon/img/no.png");

  ui->pictureLabel->setPixmap(QPixmap::fromImage(checkOk));
  ui->pictureLabel->hide();

  ui->pictureLabel_No->setPixmap(QPixmap::fromImage(checkNo));
  ui->pictureLabel_No->hide();

  if (idScientist == 0) {
	  setUpForAdd();
  }
  else{
	  setUpForEdit();
  }
}

AddDialog::~AddDialog()
{
  delete ui;
}

void AddDialog::setUpForAdd(){
    ui->addToDB->setText("Add");
	ui->bornAddSpinBox->setMinimum(1000);
	ui->bornAddSpinBox->setMaximum(QDate::currentDate().year());
	ui->bornAddSpinBox->setValue(1900);
	ui->bornAddSpinBox->setReadOnly(false);

	ui->diedAddSpinBox->setMinimum(ui->bornAddSpinBox->value() + 10);
	ui->diedAddSpinBox->setMaximum(QDate::currentDate().year());
	ui->diedAddSpinBox->setReadOnly(false);
}

void AddDialog::setUpForEdit(){

    ui->addToDB->setText("Edit");

    QString   getScientistQuery = QString::number(idScientist);
    scientistEdit    =
      (services.searchScientists("?? id=" + getScientistQuery)).at(0);

    QString fName      = QString::fromStdString(scientistEdit.getF());
    QString lName      = QString::fromStdString(scientistEdit.getL());
    QString qGender  = QString::number(scientistEdit.getGender());
    int     bornYear   = (scientistEdit.getYearBorn());
    int     deathYear  = (scientistEdit.getYearDied());
    QString knownForIt = QString::fromStdString(scientistEdit.getKnownFor());


    QString fullName = fName + " " + lName;
    name = fullName;
    ui->nameLineEdit->setText(name);
    on_nameLineEdit_textEdited(name);

    if(qGender == "1"){
        ui->gendrComboBox->setCurrentIndex(1);
    }
    else{
        ui->gendrComboBox->setCurrentIndex(0);
    }

    ui->bornAddSpinBox->setValue(bornYear);

    if (deathYear == 0) {
      ui->aliveAddcheckBox->setChecked(true);
      ui->diedAddSpinBox->setEnabled(false);
    }
    else
    {
      ui->diedAddSpinBox->setValue(deathYear);
    }
    ui->knownForText->setPlainText(knownForIt);
}



void AddDialog::on_bornAddSpinBox_editingFinished(){
  ui->diedAddSpinBox->setMinimum(ui->bornAddSpinBox->value() + 10);
  ui->diedAddSpinBox->setMaximum(QDate::currentDate().year());
  ui->bornAddSpinBox->setReadOnly(false);
}

void AddDialog::on_aliveAddcheckBox_clicked(bool checked){
  if (checked) {
    ui->diedAddSpinBox->setEnabled(false);
  } else {
    ui->diedAddSpinBox->setEnabled(true);
  }
}

void AddDialog::on_bornAddSpinBox_valueChanged(int arg1){
  if (arg1 < 1900) {
    ui->aliveAddcheckBox->setEnabled(false);
  } else {
    ui->aliveAddcheckBox->setEnabled(true);
  }
}

void AddDialog::on_addToDB_pressed(){

  on_bornAddSpinBox_editingFinished();
  isNameGood();

  if (name.size() < 1) {
    QMessageBox::warning(0, "Error", "Name field is empty");
  }
  else {
    if(idScientist==0){
		addToDatabaseConfirm();
	}
	else{
		updateDatabaseConfirm();
	}
  }
}
void AddDialog::addToDatabaseConfirm(){
    QString confirmationText, alive;
    int     dYear;

    if (ui->aliveAddcheckBox->isChecked()) {
      alive = "Still alive";
      dYear = NULL;
    } else {
      alive = QString::number(ui->diedAddSpinBox->value());
      dYear = ui->diedAddSpinBox->value();
    }



    confirmationText = QString("Confirm \n\nName: %1\nGender: %2\nBorn: %3\nDied: %4\nKnown for: %5 \n\n"
                  "Are you sure you want to add this entry?")
          .arg(name).arg(ui->gendrComboBox->currentText()).arg(
      ui->bornAddSpinBox->value()).arg(alive).arg(knownFor);

    QMessageBox addMsgBox;
    addMsgBox.setWindowTitle("Confirm");
    //addMsgBox.setTextFormat(Qt::TextWordWrap);
    addMsgBox.setText(confirmationText);
    QAbstractButton *pButtonYes = addMsgBox.addButton(tr("Yes"), QMessageBox::YesRole);
    addMsgBox.addButton(tr("No"), QMessageBox::NoRole);

    addMsgBox.exec();

    if (addMsgBox.clickedButton() == pButtonYes) {
      string nameIs     = name.toStdString();
      string knownForIs = knownFor.toStdString();
      string gender;
      int    bYear = ui->bornAddSpinBox->value();

      if (ui->gendrComboBox->currentText() == "Female") {
        gender = "f";
      }
      else{
        gender = "m";
      }


      if (services.createScientistToAdd(nameIs, gender, bYear, dYear, knownForIs)){
        QMessageBox::information(0,
                                 "Added to database",
                                 "Entry sucsessfully added to database");
        on_clearEdit_clicked();
      }
      else{
        QMessageBox::warning(0, "Error",
                             "Error! \n\nUnable to add to database");
      }
    }
}

void AddDialog::updateDatabaseConfirm(){

        QString newScientistInfo, oldScientistInfo, confirmationText, alive;
        int     dYear;

        if (ui->aliveAddcheckBox->isChecked()) {
          alive = "Still alive";
          dYear = NULL;
        }
        else {
          alive = QString::number(ui->diedAddSpinBox->value());
          dYear = ui->diedAddSpinBox->value();
        }
        QString qGender= QString::number(scientistEdit.getGender());

        QString oldScientistFName = QString::fromStdString(scientistEdit.getF());
        QString oldScientistLName = QString::fromStdString(scientistEdit.getL());
        QString oldFullName = oldScientistFName + " " + oldScientistLName;
        QString oldGender;
        if(qGender == "1"){
           oldGender = "Female";
        }else{
           oldGender = "Male";
        }

        QString oldYearBorn = QString::number(scientistEdit.getYearBorn());
        QString oldYearDied = QString::number(scientistEdit.getYearDied());
        if(oldYearDied == "0"){
            oldYearDied ="Still Alive";
        }

        QString oldKnownFor = QString::fromStdString(scientistEdit.getKnownFor());

        oldScientistInfo=QString::number(scientistEdit.getId());
        oldScientistInfo = QString("Name: %1\nGender: %2\nBorn: %3\nDied: %4\nKnown for: %5 \n\n")
                                    .arg(oldFullName).arg(oldGender).arg(oldYearBorn).arg(oldYearDied).arg(oldKnownFor);

        newScientistInfo = QString("Name: %1\nGender: %2\nBorn: %3\nDied: %4\nKnown for: %5 \n\n")
                                    .arg(name).arg(ui->gendrComboBox->currentText()).arg(
                                    ui->bornAddSpinBox->value()).arg(alive).arg(knownFor);

        confirmationText= QString("Confirm change from:\n"+oldScientistInfo+"\n\nTo:\n"+newScientistInfo+"\n\nAre you sure you want to update?");

        QMessageBox addMsgBox;
        addMsgBox.setFixedSize(200,300);
        addMsgBox.setWindowTitle("Confirm");
        addMsgBox.setText(confirmationText);
        QAbstractButton *pButtonYes = addMsgBox.addButton(tr("Yes"), QMessageBox::YesRole);
        addMsgBox.addButton(tr("No"), QMessageBox::NoRole);
        addMsgBox.exec();

        if (addMsgBox.clickedButton() == pButtonYes) {
			string nameIs     = name.toStdString();
			string lastname = "last";
			string knownForIs = knownFor.toStdString();
			bool   gender;
			int    bYear = ui->bornAddSpinBox->value();
			int    id    = scientistEdit.getId();


          if (ui->gendrComboBox->currentText() == "Female") {
            gender = true;
          }
          else{
            gender = false;
          }

          Scientist updatedScientist(id, nameIs, lastname, gender, bYear, dYear, knownForIs);

          if (services.updateScientist(updatedScientist)){
            QMessageBox::information(0,
                                     "Added to database",
                                     "Entry sucsessfully updated in database");
            on_clearEdit_clicked();
          }
          else{
            QMessageBox::warning(0, "Error",
                                 "Error! \n\nUnable to update database");
          }
        }
}

void AddDialog::on_nameLineEdit_textEdited(const QString& arg1){

  name = ui->nameLineEdit->text();

  if (arg1.size() < 1)
  {
    ui->pictureLabel->hide();
    ui->pictureLabel_No->hide();
    ui->addToDB->setEnabled(false);
  }
  else if (isNameGood()) {
    ui->pictureLabel->show();
    ui->pictureLabel_No->hide();
    ui->addToDB->setEnabled(true);
  }
  else
  {
    ui->pictureLabel->hide();
    ui->pictureLabel_No->show();
    ui->addToDB->setEnabled(false);
  }
}

void AddDialog::on_knownForText_textChanged()
{
  knownFor = ui->knownForText->toPlainText();
}

bool AddDialog::isNameGood() {
  string nameIs = name.toStdString();
    if(nameIs.empty() || nameIs[0] == ' '){
        return false;
    }
  for (unsigned int i = 0; i < nameIs.length(); i++) {
    if ((islower(nameIs[0])) || (islower(nameIs[i]) && (nameIs[i - 1] == ' '))) {
      nameIs[i] = toupper(nameIs[i]);
    }
    else if (!isalpha(nameIs[i])) {
      if ((nameIs[i] == ' ') && (nameIs[i + 1] == ' ')) {
        nameIs.erase(nameIs.begin() + i);
        i--;
      } else if (nameIs[i] != ' ') {
        return false;
      }
    } else if ((i != 0) && (isupper(nameIs[i]) && (nameIs[i - 1] != ' '))) {
      nameIs[i] = tolower(nameIs[i]);
    } else if (nameIs == "") {
      return false;
    }
  }
  name = QString::fromStdString(nameIs);
  return true;
}

void AddDialog::on_exitAddWindow_clicked()
{
  this->close();
}

void AddDialog::on_clearEdit_clicked()
{
  ui->nameLineEdit->clear();
  ui->knownForText->clear();
  ui->bornAddSpinBox->setValue(1900);
  ui->diedAddSpinBox->setValue(ui->bornAddSpinBox->value() + 10);
  ui->aliveAddcheckBox->setChecked(false);
  ui->pictureLabel->hide();
  ui->pictureLabel_No->hide();
}
