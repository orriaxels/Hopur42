#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "services/service.h"
#include "models/computer.h"
#include "models/scientist.h"
#include "adddialog.h"
#include "addcompdialog.h"
#include "addrelationdialog.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

const QString GOOGLE_SEARCH = "http://www.google.com/search?q=";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    intilizeScientistTable();
    displayScientistList(services.getSortedScientistList());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_scientistRadioButton_toggled(bool checked) {
    intilizeScientistTable();
    displayScientistList(services.searchScientists(ui->lineEdit->text()));
}

void MainWindow::intilizeScientistTable() {
    ui->buttunAdd->setText("Add scientist...");
    ui->buttonEdit->setText("Edit scientist...");
    ui->buttunRemove->setText("Remove scientist...");
    ui->detailsLabel->setText("Select entery for more information.");
    ui->buttonEdit->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->mainTable->clearSelection();
    ui->mainTable->setColumnCount(7);
    ui->mainTable->setColumnWidth(0, 0);
    ui->mainTable->setColumnWidth(1, 120);
    ui->mainTable->setColumnWidth(2, 100);
    ui->mainTable->setColumnWidth(3, 80);
    ui->mainTable->setColumnWidth(4, 80);
    ui->mainTable->setColumnWidth(5, 80);

    QStringList columns;
    columns << "id" << "First name" << "Last name" << "Gender" << "Born"
            << "Died" << "Known for";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->sortByColumn(1, Qt::AscendingOrder);
    ui->mainTable->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    ui->mainTable->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignLeft);
    ui->mainTable->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(5)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(6)->setTextAlignment(Qt::AlignLeft);
}

void MainWindow::displayScientistList(std::vector<Scientist> listToDisplay) {

    ui->mainTable->clearContents();
    ui->mainTable->setSortingEnabled(false);
    ui->mainTable->setRowCount(listToDisplay.size());

    for (unsigned int i = 0; i < listToDisplay.size(); i++) {
    	QString id    = QString::number(((listToDisplay.at(i)).getId()));
    	QString fName = QString::fromStdString(((listToDisplay.at(i)).getF()));
    	QString lName = QString::fromStdString(((listToDisplay.at(i)).getL()));
    	QString gender;

    	if ((listToDisplay.at(i)).getGender()) {
    	    gender = "Female";
    	}
    	else {
    	    gender = "Male";
    	}
    	QString born = QString::number((listToDisplay.at(i)).getYearBorn());
    	QString died = QString::number((listToDisplay.at(i)).getYearDied());

    	if (died == "0") {
    	    died = "Alive";
    	}

    	QString known = QString::fromStdString(((listToDisplay.at(i)).getKnownFor()));

    	ui->mainTable->setItem(i, 0, new QTableWidgetItem(id));
    	ui->mainTable->setItem(i, 1, new QTableWidgetItem(fName));
    	ui->mainTable->setItem(i, 2, new QTableWidgetItem(lName));
    	ui->mainTable->setItem(i, 3, new QTableWidgetItem(gender));
    	ui->mainTable->item(i, 3)->setTextAlignment(Qt::AlignCenter);
    	ui->mainTable->setItem(i, 4, new QTableWidgetItem(born));
    	ui->mainTable->item(i, 4)->setTextAlignment(Qt::AlignCenter);
    	ui->mainTable->setItem(i, 5, new QTableWidgetItem(died));
    	ui->mainTable->item(i, 5)->setTextAlignment(Qt::AlignCenter);
    	ui->mainTable->setItem(i, 6, new QTableWidgetItem(known));
    }
    ui->mainTable->setSortingEnabled(true);
    ui->mainTable->selectRow(0);
}

void MainWindow::on_computerRadioButton_toggled(bool checked) {
    intilizeComputerTable();
    displayComputerList(services.searchComputers(ui->lineEdit->text()));
}

void MainWindow::intilizeComputerTable() {
    ui->buttunAdd->setText("Add computer...");
    ui->buttonEdit->setText("Edit computer...");
    ui->buttunRemove->setText("Remove computer...");
    ui->detailsLabel->setText("Select entery for more information.");
    ui->buttonEdit->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->mainTable->clearSelection();
    ui->mainTable->setColumnCount(5);
    ui->mainTable->setColumnWidth(0, 0);
    ui->mainTable->setColumnWidth(1, 200);
    ui->mainTable->setColumnWidth(2, 200);
    ui->mainTable->setColumnWidth(3, 100);

    QStringList columns;
    columns << "id" << "Name" << "Type" << "Built" << "Built year";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->sortByColumn(1, Qt::AscendingOrder);
    ui->mainTable->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignHCenter);
    ui->mainTable->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignLeft);
}

void MainWindow::displayComputerList(std::vector<Computer>listToDisplay) {
    ui->mainTable->clearContents();
    ui->mainTable->setSortingEnabled(false);
    ui->mainTable->setRowCount(listToDisplay.size());

    for (unsigned int i = 0; i < listToDisplay.size(); i++) {
    	QString id   = QString::number(((listToDisplay.at(i)).getId()));
    	QString name = QString::fromStdString(((listToDisplay.at(i)).getName()));
    	QString type = QString::fromStdString(((listToDisplay.at(i)).getType()));
    	QString built, builtYear;

    	if ((listToDisplay.at(i)).getBuild()) {
    	    built     = "Yes";
    	    builtYear = QString::number((listToDisplay.at(i)).getBuildYear());
    	}
    	else {
    	    built     = "No";
    	    builtYear = "";
    	}

    	ui->mainTable->setItem(i, 0, new QTableWidgetItem(id));
    	ui->mainTable->setItem(i, 1, new QTableWidgetItem(name));
    	ui->mainTable->setItem(i, 2, new QTableWidgetItem(type));
    	ui->mainTable->setItem(i, 3, new QTableWidgetItem(built));
    	ui->mainTable->item(i, 3)->setTextAlignment(Qt::AlignCenter);
    	ui->mainTable->setItem(i, 4, new QTableWidgetItem(builtYear));
    }
    ui->mainTable->setSortingEnabled(true);
    ui->mainTable->selectRow(0);
}

void MainWindow::on_relationRadioButton_toggled(bool checked) {
    intilizeRelationTable();
    displayRelationTable();
}

void MainWindow::intilizeRelationTable() {
    ui->buttunAdd->setText("Add relation...");
    ui->buttonEdit->setText("Edit relation...");
    ui->buttunRemove->setText("Remove relation...");
    ui->detailsLabel->setText("Select entery for more information.");
    ui->buttonEdit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->mainTable->clearSelection();
    ui->mainTable->setColumnCount(4);
    ui->mainTable->setColumnWidth(0, 0);
    ui->mainTable->setColumnWidth(1, 300);
    ui->mainTable->setColumnWidth(2, 0);

    QStringList columns;
    columns << "idScientist" << "Scientists name" << "idComputers"
            << "Computer name";
    ui->mainTable->setHorizontalHeaderLabels(columns);
    ui->mainTable->sortByColumn(1, Qt::AscendingOrder);
    ui->mainTable->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignLeft);
}

void MainWindow::displayRelationTable() {
    ui->mainTable->clearContents();
    ui->mainTable->setSortingEnabled(false);
    vector<Scientist> scientistsSorted = services.getSortedScientistList();
    vector<Computer>  bufferComputerList;
    int rowCount = services.numberOfRelations();
    int indexRow = 0;
    ui->mainTable->setRowCount(rowCount);

    for (unsigned int i = 0; i < scientistsSorted.size(); i++) {
    	bufferComputerList = services.getAssociatedComputers(scientistsSorted.at(i));

    	if (bufferComputerList.size() > 0) {
    	    for (unsigned int j = 0; j < bufferComputerList.size(); j++) {
        		QString idScientist   = QString::number((scientistsSorted.at(i)).getId());
        		QString nameScientist = QString::fromStdString((scientistsSorted.at(i)).getF())
        		                + " " + QString::fromStdString((scientistsSorted.at(i)).getL());
        		QString idComputer    = QString::number((bufferComputerList.at(j)).getId());
        		QString nameComputer  = QString::fromStdString((bufferComputerList.at(j)).getName());

        		ui->mainTable->setItem(indexRow, 0, new QTableWidgetItem(idScientist));
        		ui->mainTable->setItem(indexRow, 1, new QTableWidgetItem(nameScientist));
        		ui->mainTable->setItem(indexRow, 2, new QTableWidgetItem(idComputer));
        		ui->mainTable->setItem(indexRow, 3, new QTableWidgetItem(nameComputer));
        		indexRow++;
    	    }
    	}
    }
    ui->mainTable->setSortingEnabled(true);
    ui->mainTable->selectRow(0);
}

void MainWindow::on_lineEdit_textChanged(const QString& arg1) {
    if (ui->scientistRadioButton->isChecked()) {
        displayScientistList(services.searchScientists(arg1));
    }
    else if (ui->computerRadioButton->isChecked()) {
        displayComputerList(services.searchComputers(arg1));
    }
}

void MainWindow::on_actionAbout_us_triggered() {
    QMessageBox::information(this, tr("About us"),tr(
                 "<p>This program lets you view and edit small databases of scientists and computers.</p>"
                 "<p>More information is on  <a href=\"https://github.com/orriaxels/Hopur42\" style=\"color:blue\">Github</a> </p> "
                 "<p>Group <a href=\"https://www.youtube.com/watch?v=dQw4w9WgXcQ\" style=\"color:blue\">Web page</a> </p>"));
}

void MainWindow::on_addScientist_triggered() {
    AddDialog add(0);
    add.setModal(true);
    add.exec();
}

void MainWindow::databaseFailedOpen() {
    QMessageBox::critical(this, tr("Database fail!"),
                        tr("The program was not able to open the database."
                        " <p> Check if database exists or path of database.</p>"));
}

void MainWindow::on_buttunAdd_clicked() {
    if (ui->scientistRadioButton->isChecked()) {
    	AddDialog add(0);
    	add.setModal(true);
    	add.exec();
    }
    else if (ui->computerRadioButton->isChecked()) {
    	AddCompDialog addComp(0);
    	addComp.setModal(true);
    	addComp.exec();
    }
    else if (ui->relationRadioButton->isChecked()) {
    	AddRelationDialog addRelations;
    	addRelations.setModal(true);
    	addRelations.exec();
    }
}

void MainWindow::on_buttunRemove_clicked() {
    if (ui->mainTable->selectedItems().size() != 0) {
    	int indexRow = ui->mainTable->currentRow();

    	QMessageBox confirmRemove;
    	confirmRemove.setStandardButtons(QMessageBox::Yes);
    	confirmRemove.addButton(QMessageBox::No);
    	confirmRemove.setDefaultButton(QMessageBox::No);
    	confirmRemove.setWindowTitle(tr("Are you sure?"));

    	if (ui->scientistRadioButton->isChecked()) {
    	    QString firstName = ui->mainTable->item(indexRow, 1)->text();
    	    QString lastName  = ui->mainTable->item(indexRow, 2)->text();
    	    int     id        = ui->mainTable->item(indexRow, 0)->text().toUInt();

    	    confirmRemove.setText(("<p>You are about remove "
    	                           "<b>" + firstName + " " + lastName +
    	                           "</b> from the database.</p>"
    	                           "Are you sure you want to proceed?"));

    	    if (confirmRemove.exec() == QMessageBox::Yes) {
        		if (services.removeScientist(id)) {
        		    ui->statusBar->showMessage("Succsessfully removed " + firstName
                                    + " " + lastName + " from the database.",5000);
        		    displayScientistList(services.searchScientists(ui->lineEdit->text()));
        		}
        		else {
        		    ui->statusBar->showMessage( "Unable to remove " + firstName
                            + " " + lastName + " from the database.", 5000);
        		}
    	    }
    	}
    	else if (ui->computerRadioButton->isChecked()) {
    	    QString name = ui->mainTable->item(indexRow, 1)->text();
    	    int     id   = ui->mainTable->item(indexRow, 0)->text().toUInt();

    	    confirmRemove.setText(("<p>You are about remove " "<b>" + name
                        + " </b> from the database.</p> Are you sure you want to proceed?"));

    	    if (confirmRemove.exec() == QMessageBox::Yes) {
        		if (services.removeComputer(id)) {
        		    ui->statusBar->showMessage("Succsessfully removed " + name
                                            + " from the database.", 3000);
        		    displayComputerList(services.searchComputers(ui->lineEdit->text()));
        		}
        		else {
        		    ui->statusBar->showMessage("Unable to remove " + name + " from the database.", 5000);
        		}
    	    }
    	}
    	else if (ui->relationRadioButton->isChecked()) {
    	    int     idScientist   = ui->mainTable->item(indexRow, 0)->text().toUInt();
    	    QString scientistName = ui->mainTable->item(indexRow, 1)->text();
    	    int     idComputer    = ui->mainTable->item(indexRow, 2)->text().toUInt();
    	    QString computerName  = ui->mainTable->item(indexRow, 3)->text();

    	    confirmRemove.setText(("<p>You are about remove relation between <b>"
                        + scientistName + " and " + computerName + "</b> from the "
                        "database.</p>Are you sure you want to proceed?"));

    	    if (confirmRemove.exec() == QMessageBox::Yes) {
        		if (services.removeRelation(idScientist, idComputer)) {
        		    ui->statusBar->showMessage("Succsessfully removed relation from the database.",3000);
        		    displayRelationTable();
        		}
        		else {
        		    ui->statusBar->showMessage("Unable to remove relation from the database.", 5000);
        		}
    	    }
    	}
    }
    else {
       ui->statusBar->showMessage("You have to select a row first.", 5000);
    }
}

void MainWindow::on_addComputer_triggered() {
    AddCompDialog addComp(0);
    addComp.setModal(true);
    addComp.exec();
}

void MainWindow::on_addRelation_triggered() {
    AddRelationDialog addRelations;
    addRelations.setModal(true);
    addRelations.exec();
}

void MainWindow::on_pushButton_clicked() {

    QMessageBox::information(this, tr("How to filter"),
                     tr("<p><b>Simple search:</b><br>"
                        "When you type somthing into  you search in all columns<br>"
                        "For example searching: \"ada enigma\" <br>"
                        "Will return:            Ada Lovelace and Alan Turing.<br>"
                        "Because Ada's name and Alan worked on the computer Enigma<br></p>"
                        "<p><b>Advanced search:</b><br>"
                        "Type \"??\" in start of filter to use advanced search.<br>"
                        "This appends the \"WHERE\" statement for current table.<br>"
                        "For example searching: \"Born > '1900' OR First name =\"bill\" <br>"
                        "Will return: those born after 1900 and also those with first name Bill.</p>"
                        "<p>See <a href=\"https://www.sqlite.org/syntax/expr.html\" "
                        "style=\"color:blue\">SQLite documentation</a> for more about advanced search.</p> "));
}

void MainWindow::on_buttonEdit_clicked() {

    if (ui->mainTable->selectedItems().size() > 0) {
    	int indexRow = ui->mainTable->currentRow();

    	if (ui->scientistRadioButton->isChecked()) {
    	    int idScientist = ui->mainTable->item(indexRow, 0)->text().toUInt();
    	    AddDialog modify(idScientist);
    	    modify.setModal(true);
    	    modify.exec();
            displayScientistList(services.searchScientists(ui->lineEdit->text()));
    	}
    	else if (ui->computerRadioButton->isChecked()) {
    	    int idComputer = ui->mainTable->item(indexRow, 0)->text().toUInt();
    	    AddCompDialog modify(idComputer);
    	    modify.setModal(true);
    	    modify.exec();
            displayComputerList(services.searchComputers(ui->lineEdit->text()));
    	}
    }
    else {
        ui->statusBar->showMessage("Please select a row before you do that.", 3000);
    }
}

void MainWindow::on_mainTable_currentCellChanged(int currentRow, int currentColumn,
                                                 int previousRow, int previousColumn) {
    QString link = "<html><head/><body><p>For more information click <a href=\"https\">"
                   "<span style=\" text-decoration: underline; color:#0066ff;\">here."
                   "</span></a></p></body></html> ";

    if (ui->mainTable->selectedItems().size() != 0) {
    	if (ui->scientistRadioButton->isChecked()) {
    	    QString details = "Name: " + ui->mainTable->item(currentRow, 1)->text()
                     + " " + ui->mainTable->item(currentRow, 2)->text()
                     + "<br>Gender: " + ui->mainTable->item(currentRow, 3)->text() + ".<br>"
            	     + ui->mainTable->item(currentRow, 2)->text() + " was born in "
    	             + ui->mainTable->item(currentRow, 4)->text();

    	    if (ui->mainTable->item(currentRow, 5)->text() == "Alive") {
                details += " and is still alive today. ";
    	    }
    	    else {
        		details += " and died in " + ui->mainTable->item(currentRow, 5)->text() + ".<br>";

        		if (ui->mainTable->item(currentRow, 3)->text() == "Female") {
        		    details += "She was ";
        		}
        		else {
        		    details += "He  was ";
        		}

        		int year = ui->mainTable->item(currentRow, 5)->text().toUInt()
        		         - ui->mainTable->item(currentRow, 4)->text().toUInt();

        		details += QString::number(year) + " years old when ";

        		if (ui->mainTable->item(currentRow, 3)->text() == "Female") {
        		    details += " she died. ";
        		}
        		else {
        		    details += " he died. ";
        		}
    	    }

    	    details += ui->mainTable->item(currentRow, 1)->text() + " "
                     + ui->mainTable->item(currentRow, 2)->text() + " was best known for "
    	             + ui->mainTable->item(currentRow, 6)->text();

    	    details += link;
    	    ui->detailsLabel->setText(details);
    	}

    	if (ui->computerRadioButton->isChecked()) {
    	    QString compDetails = "Name: " + ui->mainTable->item(currentRow, 1)->text()
                         + "<br>" + "Type: " + ui->mainTable->item(currentRow, 2)->text() + "<br>";

    	    if (ui->mainTable->item(currentRow, 3)->text() == "Yes") {
                compDetails += ui->mainTable->item(currentRow, 1)->text() + " was built "
                            + ui->mainTable->item(currentRow, 4)->text() + ".";
    	    }
    	    else {
                compDetails += "It was not built.";
    	    }
            compDetails+=link;
    	    ui->detailsLabel->setText(compDetails);
    	}

    	if (ui->relationRadioButton->isChecked()) {
    	    QString reDetails = ui->mainTable->item(currentRow, 1)->text()
                              + " can be associated with "
                              + ui->mainTable->item(currentRow, 3)->text()
                              + link;
    	    ui->detailsLabel->setText(reDetails);
    	}
    }
}

void MainWindow::on_removeComputer_triggered() {

    if (ui->computerRadioButton->isChecked()) {
        if (ui->mainTable->selectedItems().size() > 0) {
              on_buttunRemove_clicked();
        }
        else {
           ui->statusBar->showMessage("You have to select a computer first.", 5000);
        }
    }
    else {
       ui->statusBar->showMessage("Go to computer table and select a computer to edit.", 5000);
    }
}

void MainWindow::on_removeScientist_triggered() {
    if (ui->scientistRadioButton->isChecked()) {
        if (ui->mainTable->selectedItems().size() > 0) {
              on_buttunRemove_clicked();
        }
        else {
           ui->statusBar->showMessage("You have to select a scientist first.", 5000);
        }
    }
    else {
       ui->statusBar->showMessage("Go to scientist table and select a scientist to remove.", 5000);
    }
}

void MainWindow::on_removeRelation_triggered() {
    if (ui->relationRadioButton->isChecked()) {
        if (ui->mainTable->selectedItems().size() > 0) {
             on_buttunRemove_clicked();
        }
        else {
           ui->statusBar->showMessage("You have to select a relation first.", 5000);
        }
    }
    else {
       ui->statusBar->showMessage("Go to relation table and select a relation to remove.", 5000);
    }
}

void MainWindow::on_editScientist_triggered() {
    if (ui->scientistRadioButton->isChecked()) {
        if (ui->mainTable->selectedItems().size() > 0) {
            on_buttonEdit_clicked();
        }
        else {
           ui->statusBar->showMessage("You have to select a scientist first.", 5000);
        }
    }
    else {
       ui->statusBar->showMessage("Go to scientist table and select a scientist to edit.", 5000);
    }
}

void MainWindow::on_editComputer_triggered() {
    if (ui->computerRadioButton->isChecked()) {
        if (ui->mainTable->selectedItems().size() > 0) {
            on_buttonEdit_clicked();
        }
        else {
           ui->statusBar->showMessage("You have to select a computer first.", 5000);
        }
    }
    else {
       ui->statusBar->showMessage("Go to the computer table and select a computer to edit.", 5000);
    }
}

void MainWindow::on_detailsLabel_linkActivated(const QString& link) {
    if (ui->mainTable->selectedItems().size() != 0) {
    	int indexRow   = ui->mainTable->currentRow();
        QString buffer;
        if (ui->scientistRadioButton->isChecked()){
            buffer = ui->mainTable->item(indexRow, 1)->text() + "+" +
	                 ui->mainTable->item(indexRow, 2)->text();
        }
        if (ui->computerRadioButton->isChecked()){
            buffer = "Computer" +
	                 ui->mainTable->item(indexRow, 1)->text();
        }
        if (ui->relationRadioButton->isChecked()){
            buffer = ui->mainTable->item(indexRow, 1)->text() + "+" +
	                 ui->mainTable->item(indexRow, 3)->text();
        }

    	buffer.replace(" ", "+");
    	buffer = GOOGLE_SEARCH + buffer + "&btnI";
    	QDesktopServices::openUrl(QUrl(buffer));
    }
}
