#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>//atoi()
#include <iomanip>//for setw()

#include "ui/interface.h"
#include "services/service.h"
#include "models/computers.h"
#include "models/persons.h"

using namespace std;

InterFace::InterFace(){} //default constructor

void InterFace::runInterFace(){
        InterFace::displayMainMenu();
        InterFace::actionSelect();
}

void InterFace::actionSelect(){
  char a;
  string choice;
  bool loop;

  cout << "Please select an option from the list: ";
  do{
      cin >> choice;
  }while(! inputCheckVar.isInputGood(1, 5, choice));
  a=choice[0];

  do{
      switch(a){
      case '1':
          cout << endl;
          InterFace::printAddMenu();
          break;
      case '2':
          cout << endl;
          InterFace::printDisplayMenu();
          break;
      case '3':
          cout << endl;
          InterFace::printSearchMenu();
          break;
      case '4':
          cout<<endl;
          InterFace::printRemoveMenu();
          break;
      case '5':
          loop = 0;
          break;
      default:
          cout << "Invalid" << endl;
          break;

      }
  }while(loop);

}

void InterFace::displayMainMenu(){
    cout<< "Welcome! This database contains information about great computer scientists and computers." << endl
        << endl
        << "What would you like to do?" << endl
        << "  1. Add a new entry" << endl
        << "  2. Display database" << endl
        << "  3. Search the database" << endl
        << "  4. Remove entry from database"<<endl
        << "  5. Quit" << endl
        << endl;
}

void InterFace::printAddMenu(){
    string choice;

    cout << "Choose what to add: " << endl;
    cout << "1: Add scientist" << endl;
    cout << "2: Add computer" << endl;
    cout << "0: Cancel" << endl;
    cout << "Enter choice: ";

    do{
        cin >> choice;
    }while(! inputCheckVar.isInputGood(0, 2, choice));

    if(choice == "1"){
        printAddPersonMenu();
    }else if(choice == "0"){
        runInterFace();
    }else{
        printAddCompMenu();
    }

}

void InterFace::printAddPersonMenu(){

    string name, illegal;
    string knownFor="";
    string gender="";
    int bYear = 0;
    int dYear = 0;

    cout << "Enter information" << endl;

    //Get name input
    do{
        cout << "Name: ";
        getline(cin, name);
        if(inputCheckVar.isNameGood(name, illegal) == false){
            cout << "'" << illegal << "' "<< "not valid in name" << endl;
        }
    }while(!(inputCheckVar.isNameGood(name, illegal)));

    //Get gender input
    do{
        cout << "Gender (f=female, m=male): ";
        cin >> gender;
        if(gender != "f" && gender != "F" && gender != "m" && gender != "M"){
            cin.clear();
            cin.ignore();
            cout<<"Invalid input."<<endl;
        }
    }while(gender != "f" && gender != "F" && gender != "m" && gender != "M");

    //Get birth year input
    do{
        cout << "Year of birth: ";
        cin >> bYear;
        if(inputCheckVar.cinFailCheck(bYear)){
            cout << "Invalid input" << endl;
        }else if(inputCheckVar.checkNumber(bYear, 1800, 2010)){
            cout<<"Invalid input."<<endl;
        }

    }while(inputCheckVar.cinFailCheck(bYear) || inputCheckVar.checkNumber(bYear, 1800, 2010));

    //Get death year input
    do{
        cout << "Year of death (\"0\" if alive): ";
        cin >> dYear;
        if((inputCheckVar.cinFailCheck(dYear)) || (inputCheckVar.checkNumber(dYear, bYear+8, bYear+110) && dYear != 0)){
            cout << "Invalid input" << endl;
       }
    }while((inputCheckVar.cinFailCheck(dYear)) || (inputCheckVar.checkNumber(dYear, bYear+8, bYear+110) && dYear != 0));

    //Get input Known for info
    do{
        cout << "Is known for (\"0\" to skip): ";
        cin.ignore();
        getline(cin, knownFor);
        if((knownFor != "0") && (knownFor.length() < 3) )
            cout<<"Invalid input."<<endl;
    }while( (knownFor != "0") && (knownFor.length() < 3) );



    if( serviceVar.createPerson(name, gender, bYear, dYear, knownFor) )
      cout<<endl<<"Entry sucsessfully added to database"<<endl<<endl<<endl;
    else
      cout<<endl<<"Unable to write to database"<<endl<<endl<<endl;

    runInterFace();
}

void InterFace::printAddCompMenu(){

    string compName = "";
    string compType = "";
    string ifMade = "";
    bool wasItMade = 0; //segir til hvort talvan hafi verið byggð
    bool loop = 0;
    int yearBuilt;
    char cType;

    cout << "\n";
    cout << "Computer entry" << endl;

    do{
        cout << "Name: ";
        getline(cin, compName);
        if (compName.empty())
        {
            cout << "Invalid input, reenter" << endl;
        }
    }while(compName.empty());

    do{
        cout << "Was it built (y/n): ";
        cin >> ifMade;
        cin.ignore(1000, '\n');
        if(ifMade.empty() || ifMade.length() > 1){
            cout << "Invalid input." << endl;
        }else if(ifMade != "y" && ifMade != "Y" && ifMade != "n" && ifMade !="N" ){
            cout << "Invalid Input" << endl;
        }else if(ifMade == "y" || ifMade == "Y"){
            do{
                cout << "When was the computer built: ";
                cin >> yearBuilt;
                cin.ignore(1000, '\n');
                    if(inputCheckVar.cinFailCheck(yearBuilt)){
                        cout << "Invalid input." << endl;
                    }else if(inputCheckVar.checkNumber(yearBuilt, 1800, 2015)){
                        cout << "Invalid input." << endl;
                    }else{
                        wasItMade = 1;
                    }
                }while(!wasItMade);
            }
        }while((ifMade != "n" && ifMade != "N") && !wasItMade);

    do{
        cout << "What type of computer is it" << endl;;
        cout << "1: Mechanical" << endl;
        cout << "2: Electronic" << endl;
        cout << "3: Electro-Mechanical" << endl;
        cout << "4: Transistorized" << endl;
        cout << "choose: ";
        cin >> cType;
        cin.ignore(1000, '\n');
        if(cType !='1' && cType !='2' && cType !='3' && cType !='4'){
            cout << "Invalid Input." << endl;
        }
    }while(cType !='1' && cType !='2' && cType !='3' && cType !='4');

    do{
        switch(cType){
        case '1':
           compType = "Mechanical";
            break;
        case '2':
            compType = "Electronic";
            break;
        case '3':
            compType = "Electro-Mechanical";
            break;
        case '4':
            compType = "Transistorized";
            break;
        default:
            loop = 0;
            break;
        }
    }while(loop);

    if( serviceVar.createComputer(compName, compType, wasItMade, yearBuilt) )
      cout<<endl<<"Entry sucsessfully added to database"<<endl<<endl<<endl;
    else
      cout<<endl<<"Unable to write to database"<<endl<<endl<<endl;

    runInterFace();
}

void InterFace::printDisplayMenu(){
    string choice;
    cout << "Choose what database to display: " << endl;
    cout << "1: Display scientists database" << endl;
    cout << "2: Display computer database" << endl;
    cout << "0: Cancel" << endl;
    cout << "Enter choice: ";

    do{
        cin >> choice;
    }while(! inputCheckVar.isInputGood(0, 2, choice));

    if(choice == "1"){
        printDispPersMenu();
    }else if(choice == "0"){
        runInterFace();
    }else{
        printDispCompMenu();
    }
}

void InterFace::printDispPersMenu(){
    int sortWith, order, var;
    string choice, again;

    if(serviceVar.somthingthere()){//Checks if list is empty before printing out menu
        cout << "What would you like to sort by?" << endl
             << "1. First name" << "  ||  "
             << "2. Last name" << "  ||  "
             << "3. Gender" << "  ||  "
             << "4. Year of birth" << "  ||  "
             << "5. Year of death" << endl;
        cout << "Enter choice: ";
        do{
            cin >> choice;
        }while( ! inputCheckVar.isInputGood(1, 5, choice) ) ;
        sortWith=atoi(choice.c_str() );

        if(sortWith == 3 ){
            cout << "1. Males first" << "  ||  "
                 << "2. Females first" << endl;
        }
        else{
            cout << "1. Ascending(a-z)" << "  ||  "
                 << "2. Descending(z-a)" << endl;
        }
        cout << "Enter choice: ";
        do{
            cin >> choice;
        }while(! inputCheckVar.isInputGood(1,2, choice) );
        order=atoi(choice.c_str() );

        if (order == 1){
            printPerson( serviceVar.getSortedPersonsList(sortWith, 0) );
        }
        else if (order == 2){
            printPerson( serviceVar.getSortedPersonsList(sortWith, 1) );
        }
    }
    else{ //if database is empty does only pint this messsage
        cout<<"Nothing to display(database is empty)";
    }

    cout << endl << endl;

    cout << "1. Sort again" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> again;
    } while(! inputCheckVar.isInputGood(1,2, again));
    var = atoi(again.c_str());

    if (var == 1){
        // cool function 
        cout << "Awesome function that lets you sort again..." << endl;
    }
    else if (var == 2){
        cout << endl << endl << endl << endl;
        runInterFace();
    }
}

void InterFace::printDispCompMenu(){
    int sortWith, order, var;
    string choice, again;

    if(serviceVar.somthingthere()){//Checks if list is empty before printing out menu
        cout << "What would you like to sort by?" << endl
             << "1. Name " << "  ||  "
             << "2. Type " << "  ||  "
             << "3. Built or not " << "  ||  "
             << "4. Year built " << "  ||  " << endl
             << "Enter choice: ";
         do{
             cin >> choice;
         }while( ! inputCheckVar.isInputGood(1,4, choice) ) ;
         sortWith=atoi(choice.c_str() );


        if(sortWith ==3 ){
            cout << "1. Built first" << "  ||  "
                 << "2. Not built first" << endl;
        }
        else{
            cout << "1. Ascending(a-z/0-9)" << "  ||  "
                 << "2. Descending(z-a/9-0)" << endl;
        }

        cout << "Enter choice: ";
        do{
            cin >> choice;
        }while(! inputCheckVar.isInputGood(1,2, choice) );
        order=atoi(choice.c_str() );

        if (order == 1){
            printComputers( serviceVar.getSortedComputersList(sortWith, 0) );
        }
        else if (order == 2){
          printComputers( serviceVar.getSortedComputersList(sortWith, 1) );
        }
    }
    else{ //if database is empty does only pint this message
        cout << "Nothing to display(database is empty)";
    }

    cout << endl << endl;

    cout << "1. Sort again" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> again;
    } while(! inputCheckVar.isInputGood(1,2, again));
    var = atoi(again.c_str());

    if (var == 1){
        // cool function 
        cout << "Awesome function that lets you sort again..." << endl;
    }
    else if (var == 2){
        cout << endl << endl << endl << endl;
        runInterFace();
    }
}

void InterFace::printSearchMenu(){
    string choice;

    cout << "In what database would you like to search" << endl;
    cout << "1: Scientists" << endl;
    cout << "2: Computers" << endl;
    cout << "0: Cancel" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    }while(! inputCheckVar.isInputGood(0,2, choice) );

    if(choice == "1"){
        printPersSearchMenu();
    }else if(choice == "0"){
        runInterFace();
    }else{
        printCompSearchMenu();
    }
}

void InterFace::printPersSearchMenu(){
    string searchS, choice;
    int var;

    cout << "What would you like to search for? " ;
    getline(cin, searchS);

    serviceVar.search(searchS);

    cout << endl << endl;

    cout << "1. Search again" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(1,2, choice));
    var = atoi(choice.c_str());    
    
    if (var == 1 ){
        cout << endl << endl << endl;
        printSearchMenu();
    }
    else if(var == 2){
        cout << endl << endl << endl;
        runInterFace();
    }
}

void InterFace::printCompSearchMenu(){
    string searchS, choice;
    int var;

    cout << "What would you like to search for? ";
    getline(cin, searchS);

    serviceVar.search(searchS);

    cout << endl << endl;
    
    cout << "1. Search again" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(1,2, choice));
    var = atoi(choice.c_str());    
   
    if (var == 1 ){
        cout << endl << endl << endl;
        printSearchMenu();
    }
    else if(var == 2){
        cout << endl << endl << endl;
        runInterFace();
    }
}

void InterFace::notFound(bool wasfound, const string searchStr){
    if(wasfound)
        cout << endl << "Found \"" << searchStr << "\" in following enteries:" << endl;
    else
        cout<<"No enteries conatining \"" << searchStr << "\" found in database."<<endl;

}

void InterFace::printPerson(vector<Persons> persList){
    string buffer;

    if( persList.size() == 0) //if nothing to display
        cout<<endl<<"Nothing to display"<<endl;
    else{
        cout<<endl<<"#  Name:   \t\t\t\tGender:\tBorn:\tDied:\tKnown for:"<<endl; //header for table

        for(unsigned int i=0; i<persList.size(); i++){
            cout << i+1;
            if(i<9)
                cout<<"  ";
            else if(8<i && i<99)
                cout<<" ";

            cout << persList.at(i).getF() << " " << persList.at(i).getL();

            buffer= persList.at(i).getF() + " " + persList.at(i).getL();
            for(unsigned int j=0; j< (37- buffer.length()); j++){
                cout<<" ";
            }

            if(persList.at(i).getGender()){
                cout << "Female"<< '\t';}
            else{
                cout << "Male"<< '\t';}

            cout << persList.at(i).getYearBorn() << '\t';


            if( 0 == (persList.at(i).getYearDied()) )
                cout <<"Alive" <<'\t';
            else
                cout << persList.at(i).getYearDied() << '\t' ;


            if( "0 " == (persList.at(i).getKnownFor()) )
                cout << " " <<endl;
            else
                cout << persList.at(i).getKnownFor() << endl;
        }
    }
}

void InterFace::printComputers(vector<Computers> compList){
  string buffer;
  cout<<'\n'<<setw(3)<<left<<"#"
      <<setw(30)<<"Name:"<<setw(20)<<"Type:"<<setw(8)<<"Built:"
      <<"Year built:"<<endl;
  for(unsigned int i=0; i<compList.size(); i++){

      cout << setw(3) << left<< i+1;
      cout << setw(30)<< left<< compList.at(i).getName();
      cout << setw(20)<< compList.at(i).getType();

      if(compList.at(i).getBuild()){
          cout << setw(8)<<"Yes";}
      else{
          cout << setw(8)<< "No";}

      if( NULL == (compList.at(i).getBuildYear()) )
          cout <<"" <<'\n';
      else
          cout << compList.at(i).getBuildYear() << '\n' ;
       }
}

void InterFace::printRemoveMenu(){
    string choice;


    cout << "In what database would you like to remove data" << endl;
    cout << "1: Scientists" << endl;
    cout << "2: Computers" << endl;
    cout << "0: Cancel" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    }while(! inputCheckVar.isInputGood(0,2, choice) );

    if(choice == "1"){
        printRemovePersMenu();
    }else if(choice == "0"){
        runInterFace();
    }else{
        printRemoveCompMenu();
    }
}

void InterFace::printRemovePersMenu(){

    int enteryRemove, var;
    string choice;

    if( serviceVar.somthingthere() ){ //checs if List is empty befor displaying menu

        serviceVar.getListDatabase();
        cout<< endl << "Which one of these enteries do you want to remove(select # / 0 for cancel)? ";

        do{
            cin >> enteryRemove;

            if(cin.fail()){
                cin.clear();
                cin.get();
                cout<<"Invalid input. Enter number of entery from the list: ";
            }
        }while( (cin.fail()) );

      //  serviceVar.removeEntery(enteryRemove);
        cout << endl << "Entery sucsessfully removed. (backup_itPersons.txt contains orginal list)" << endl;
    }
    else{
        cout << "Database is empty. You can add to list in main menu." << endl;
    }

    cout << endl << endl;
    
    cout << "1. Remove something else from the list" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(1,2, choice));
    var = atoi(choice.c_str());

    if (var == 1){
        cout << endl << endl << endl;
        printRemoveMenu();
    } else if (var == 2){
        cout << endl << endl << endl;
        runInterFace();
    }
}

void InterFace::printRemoveCompMenu(){

    int enteryRemove, var;
    string choice;

    if( serviceVar.somthingthere() ){ //checs if List is empty befor displaying menu

        serviceVar.getListDatabase();
        cout<< endl << "Which one of these enteries do you want to remove(select #)? ";

        do{
            cin >> enteryRemove;

            if(cin.fail()){
                cin.clear();
                cin.get();
                cout<<"Invalid input. Enter number of entery from the list: ";
               }
        }while( (cin.fail())  );

      //  serviceVar.removeEntery(enteryRemove);
        cout << endl << "Entery sucsessfully removed. (backup_itPersons.txt contains orginal list)" << endl;
    }
    else{
        cout << "Database is empty. You can add to list in main menu." << endl;
    }

    cout << endl << endl;
    
    cout << "1. Remove something else from the list" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(1,2, choice));
    var = atoi(choice.c_str());

    if (var == 1){
        cout << endl << endl << endl;
        printRemoveMenu();
    } else if (var == 2){
        cout << endl << endl << endl;
        runInterFace();
    }

}

void InterFace::invalidInput(){
  cout << "This input is not vaild. Please try again: ";
}
