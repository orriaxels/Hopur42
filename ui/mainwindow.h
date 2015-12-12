#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "models/computer.h"
#include "models/scientist.h"
#include "services/service.h"
#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void databaseFailedOpen();
private slots:
    void on_scientistRadioButton_toggled(bool checked);

    void on_computerRadioButton_toggled(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_relationRadioButton_toggled(bool checked);

    void on_actionAbout_us_triggered();

    void on_addScientist_triggered();

private:
    Service services;
    Ui::MainWindow *ui;

    void displayScientistList(std::vector<Scientist> listToDisplay);
    void displayComputerList(std::vector<Computer> listToDisplay);

    void intilizeScientistTable(int numberOfRows);
    void intilizeComputerTable(int numberOfRows);
};

#endif // MAINWINDOW_H
