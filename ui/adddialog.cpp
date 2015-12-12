#include "adddialog.h"
#include "ui_adddialog.h"
#include <QMessageBox>
#include <QLayout>
#include <QTime>
#include <string>

using namespace std;

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    ui->bornAddSpinBox->setMinimum(1000);
    ui->bornAddSpinBox->setMaximum(QDate::currentDate().year());
    ui->bornAddSpinBox->setValue(1900);
    ui->bornAddSpinBox->setReadOnly(false);

    ui->diedAddSpinBox->setMinimum(ui->bornAddSpinBox->value()+10);
    ui->diedAddSpinBox->setMaximum(QDate::currentDate().year());
    ui->bornAddSpinBox->setReadOnly(false);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_bornAddSpinBox_editingFinished()
{
    ui->diedAddSpinBox->setMinimum(ui->bornAddSpinBox->value()+10);
    ui->diedAddSpinBox->setMaximum(QDate::currentDate().year());
    ui->bornAddSpinBox->setReadOnly(false);
}



void AddDialog::on_aliveAddcheckBox_clicked(bool checked)
{
    if(checked){
        ui->diedAddSpinBox->setEnabled(false);

    }else{
        ui->diedAddSpinBox->setEnabled(true);
    }
}

void AddDialog::on_bornAddSpinBox_valueChanged(int arg1)
{
    if(arg1 < 1900){
        ui->aliveAddcheckBox->setEnabled(false);
    }else{
        ui->aliveAddcheckBox->setEnabled(true);
    }
}

void AddDialog::on_addToDB_pressed()
{
    on_bornAddSpinBox_editingFinished();
    isNameGood();
    QString str;
    QString alive;
    int dead;
    if(ui->aliveAddcheckBox->isChecked()){
        alive = "Still alive";
    }else{
        alive = QString::number(ui->diedAddSpinBox->value());
    }
    if(name.size() < 1){
        QMessageBox::warning(0, "Ok","Name field is empty");
    }
    else{
        str = QString("Name: %1\nGender: %2\nBorn: %3\nDied: %4\nKnown for: %5").arg(name).arg(ui->gendrComboBox->currentText()).arg(ui->bornAddSpinBox->value()).arg(alive).arg(knownFor);
        QMessageBox::information(0, "Title", str);
    }
}

void AddDialog::on_nameLineEdit_editingFinished()
{

}

void AddDialog::on_nameLineEdit_textEdited(const QString &arg1)
{
    name = ui->nameLineEdit->text();
}


void AddDialog::on_knownForText_textChanged()
{
    knownFor = ui->knownForText->toPlainText();
}

bool AddDialog::isNameGood(){

    string nameIs = name.toStdString();
    for(unsigned int i = 0; i < nameIs.length(); i++){
                if((islower(nameIs[0])) || (islower(nameIs[i]) && nameIs[i-1] == ' ')){
                      nameIs[i] = toupper(nameIs[i]);
                  }
                else if(!isalpha(nameIs[i])){
                      if(nameIs[i] == ' ' && nameIs[i+1] == ' '){
                          nameIs.erase(nameIs.begin()+i);
                          i--;
                      }else if(nameIs[i] != ' ' ){
                          return false;
                      }

                  }else if( (i != 0) && (isupper(nameIs[i]) && nameIs[i-1] != ' ')){
                      nameIs[i] = tolower(nameIs[i]);
                  }
     }
    name = QString::fromStdString(nameIs);
    return true;
}

