#ifndef ADDCOMPDIALOG_H
#define ADDCOMPDIALOG_H

#include <QDialog>
#include "models/computer.h"
#include "services/service.h"


namespace Ui {
class AddCompDialog;
}

class AddCompDialog : public QDialog{
    Q_OBJECT

public:
        explicit AddCompDialog(int id,QWidget *parent = 0);
        ~AddCompDialog();

private slots:
        void on_buttonAdd_clicked();
        void on_radioYes_clicked();
        void on_radioNo_clicked();
        void on_buttonReset_clicked();

private:
        Ui::AddCompDialog *ui;

        int idOfComputer;
        Computer editComputer;
        Service services;

        void setUpForAdd();
        void setUpForEdit();
        void confirmNew();
        void confirmEdit();
};

#endif // ADDCOMPDIALOG_H
