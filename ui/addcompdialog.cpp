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

    QString str, compType;
    QString compName = ui->nameCompLineEdit->text();
    QString built;

    if(ui->yesRadioButton->isChecked()){
        built = QString::number(ui->builtYearAddSpinBox->value());
    }else{
        built = "It was not built.";
    }

    if(compName.size() < 1)
    {
        QMessageBox::warning(0, "Error","Name field is empty");
    }
    else if(ui->compTypecomboBox->currentText() =="Choose...")
    {
        QMessageBox::warning(0,"Error", "Choose computer type");
    }
    else
    {
        compType = ui->compTypecomboBox->currentText();
        str = QString("Confirm \n\nName: %1\nWhen was it built: %2\nType: %3\ \n\nAre you sure you want to add this to the database ?").arg(compName).
        arg(built).arg(compType);
        QMessageBox addCompMsgBox;
        addCompMsgBox.setText(str);
        QAbstractButton* pButtonYes = addCompMsgBox.addButton(tr("Yes"), QMessageBox::YesRole);
        addCompMsgBox.addButton(tr("No"), QMessageBox::NoRole);

        addCompMsgBox.exec();
        if(addCompMsgBox.clickedButton() == pButtonYes){

        }
        else
        {

        }

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

void AddCompDialog::on_clearAddComp_clicked()
{
    ui->nameCompLineEdit->clear();
    ui->yesRadioButton->setChecked(true);
    ui->noRadioButton->setChecked(false);
    ui->builtYearAddSpinBox->setEnabled(true);
    ui->builtYearAddSpinBox->setValue(1900);
    ui->compTypecomboBox->setCurrentIndex(0);
}
