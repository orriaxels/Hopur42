#include "adddialog.h"
#include "ui_adddialog.h"
#include <QLayout>
#include <QTime>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    ui->bornAddSpinBox->setMinimum(1000);
    ui->bornAddSpinBox->setMaximum(QDate::currentDate().year());
    ui->bornAddSpinBox->setValue(1900);
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
    int bornValue = ui->bornAddSpinBox->value();

    if(bornValue < 1900){
        ui->AliveAddcheckBox->setEnabled(false);
    }
    else{
        ui->AliveAddcheckBox->setEnabled(true);
    }
}



void AddDialog::on_AliveAddcheckBox_clicked(bool checked)
{
    if(checked && ui->bornAddSpinBox->value() < 1900){
        ui->AliveAddcheckBox->setEnabled(false);
        ui->diedAddSpinBox->setEnabled(true);
    }
    else if(checked){
        ui->diedAddSpinBox->setEnabled(false);

    }else{
        ui->diedAddSpinBox->setEnabled(true);
    }
}

void AddDialog::on_bornAddSpinBox_valueChanged(int arg1)
{
    if(arg1 < 1900){
        ui->AliveAddcheckBox->setEnabled(false);
    }else{
        ui->AliveAddcheckBox->setEnabled(true);
    }
}
