#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "services/service.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

    void setIdScientist(int idToSet);

private slots:
    void on_bornAddSpinBox_editingFinished();



    void on_aliveAddcheckBox_clicked(bool checked);

    void on_bornAddSpinBox_valueChanged(int arg1);

    void on_addToDB_pressed();

    void on_nameLineEdit_textEdited(const QString &arg1);

    bool isNameGood();


    void on_knownForText_textChanged();

    void on_exitAddWindow_clicked();

    void on_clearEdit_clicked();

private:
    Ui::AddDialog *ui;
    Service serviceVar;

    QString name;
    QString knownFor;
    int idScientist;
};

#endif // ADDDIALOG_H
