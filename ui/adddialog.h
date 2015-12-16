#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "services/service.h"

namespace Ui {
        class AddDialog;
}

class AddDialog : public QDialog{
        Q_OBJECT

public:
        explicit AddDialog(int idScientistToEdit, QWidget *parent = 0);
        ~AddDialog();

private slots:
        void on_bornAddSpinBox_editingFinished();
        void on_aliveAddcheckBox_clicked(bool checked);
        void on_bornAddSpinBox_valueChanged(int arg1);
        void on_addToDB_pressed();
        void on_nameLineEdit_textEdited(const QString &arg1);
        void on_knownForText_textChanged();
        void on_clearEdit_clicked();

private:
        Ui::AddDialog *ui;
        Service services;

        QString name;
        QString knownFor;
        int idScientist;
        Scientist scientistEdit;

        bool isNameGood();
        void setUpForAdd();
        void setUpForEdit();
        void addToDatabaseConfirm();
        void updateDatabaseConfirm();

};

#endif // ADDDIALOG_H
