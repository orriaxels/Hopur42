#ifndef ADDCOMPDIALOG_H
#define ADDCOMPDIALOG_H

#include <QDialog>

namespace Ui {
class AddCompDialog;
}

class AddCompDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCompDialog(int id,QWidget *parent = 0);
    ~AddCompDialog();

private slots:
    void on_addCompToDB_clicked();
    void on_yesRadioButton_clicked();
    void on_noRadioButton_clicked();
    void on_exitCompAddWindow_clicked();
    void on_clearAddComp_clicked();

private:
    Ui::AddCompDialog *ui;
    int idOfComputer;
};

#endif // ADDCOMPDIALOG_H
