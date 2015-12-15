#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "models/computer.h"
#include "models/scientist.h"
#include "services/service.h"
#include <QMainWindow>
#include <vector>
#include <QString>



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

    void on_addComputer_triggered();

    void on_addRelation_triggered();

    void on_editScientist_triggered();

    void on_editComputer_triggered();

    void on_removeScientist_triggered();

    void on_removeComputer_triggered();

    void on_removeRelation_triggered();

    void on_buttunAdd_clicked();

    void on_buttunRemove_clicked();

    void on_pushButton_clicked();

    void on_buttonEdit_clicked();

    void on_mainTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);


    void on_linkLabel_linkActivated(const QString &link);

private:
    Service services;
    Ui::MainWindow *ui;

    void displayScientistList(std::vector<Scientist> listToDisplay);
    void displayComputerList(std::vector<Computer> listToDisplay);
	void displayRelationTable();

    void intilizeScientistTable();
    void intilizeComputerTable();
	void intilizeRelationTable();

    vector<Scientist> scientistsInTable;
};

#endif // MAINWINDOW_H
