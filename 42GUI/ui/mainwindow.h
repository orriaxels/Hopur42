#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "services/service.h"
#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_scientistRadioButton_toggled(bool checked);

    void on_computerRadioButton_toggled(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_relationRadioButton_toggled(bool checked);

    void on_actionAbout_us_triggered();

    void on_addScientist_triggered();

    void on_buttonRemove_pressed();

    void on_buttonAdd_pressed();

private:
    Service services;
    Ui::MainWindow *ui;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H
