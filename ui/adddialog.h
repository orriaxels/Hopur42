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



    void on_aliveAddcheckBox_clicked(bool checked);

    void on_bornAddSpinBox_valueChanged(int arg1);

    void on_addToDB_pressed();

    void on_nameLineEdit_editingFinished();

    void on_nameLineEdit_textEdited(const QString &arg1);

    bool isNameGood();


    void on_knownForText_textChanged();

private:
    Ui::AddDialog *ui;
    QString name;
    QString knownFor;
};

#endif // ADDDIALOG_H
