#ifndef ADDRELATIONDIALOG_H
#define ADDRELATIONDIALOG_H

#include <QDialog>
#include <QString>
#include "services/service.h"
#include "models/computer.h"
#include "models/scientist.h"

namespace Ui {
        class AddRelationDialog;
}

class AddRelationDialog : public QDialog
{
        Q_OBJECT

public:
        explicit AddRelationDialog(QWidget *parent = 0);
        ~AddRelationDialog();

private slots:
        void on_lineEditScientistFilter_textChanged(const QString &arg1);
        void on_lineEditComputerFilter_textChanged(const QString &arg1);
        void on_tableScientists_doubleClicked(const QModelIndex &index);
        void on_tableComputers_doubleClicked(const QModelIndex &index);
        void on_buttonAdd_clicked();
        void on_buttonClear_clicked();

private:
        Ui::AddRelationDialog *ui;

        Service services;
        int idScientist;
        int idComputer;
        QString nameScientist;
        QString nameComputer;

        void intilizeTables();
        void previewRelationDisplay();
        void displayScientistList(vector<Scientist> listToDisplay);
        void displayCompterList(vector<Computer> listToDisplay);
};

#endif // ADDRELATIONDIALOG_H
