#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

private slots:
    void on_bornAddSpinBox_editingFinished();



    void on_AliveAddcheckBox_clicked(bool checked);

    void on_bornAddSpinBox_valueChanged(int arg1);

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
