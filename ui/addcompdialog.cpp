#include "addcompdialog.h"
#include "ui_addcompdialog.h"
#include <QMessageBox>
#include <QLayout>
#include <QTime>
#include <string>
#include <QPixmap>

using namespace std;

AddCompDialog::AddCompDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompDialog)
{
    ui->setupUi(this);

    ui->builtYearAddSpinBox->setMinimum(1000);
    ui->builtYearAddSpinBox->setMaximum(QDate::currentDate().year());
    ui->builtYearAddSpinBox->setValue(1900);
    ui->builtYearAddSpinBox->setReadOnly(false);

}

AddCompDialog::~AddCompDialog()
{
    delete ui;
}

void AddCompDialog::on_addCompToDB_clicked()
{

    QString str;
    QString compName = ui->nameCompLineEdit->text();
    QString built;

    if(ui->yesRadioButton->isChecked()){
        built = ui->builtYearAddSpinBox->value();
    }else{
        built = "It was not built.";
    }

    if(compName.size() < 1){
        QMessageBox::warning(0, "Error","Name field is empty");
    }
    else{
        str = QString("Name: %1\nWhen was it built: %2\nType: %3\ \n\nAre you sure you want to add this to the database ?").arg(compName).
        arg(built).arg(ui->compTypecomboBox->currentText());
        QMessageBox::information(0, "Confirm?", str, QMessageBox::No|QMessageBox::Yes);
    }
}



void AddCompDialog::on_yesRadioButton_clicked()
{
    ui->builtYearAddSpinBox->setEnabled(true);
}

void AddCompDialog::on_noRadioButton_clicked()
{
    ui->builtYearAddSpinBox->setEnabled(false);
}

void AddCompDialog::on_exitCompAddWindow_clicked()
{
    this->close();
}
