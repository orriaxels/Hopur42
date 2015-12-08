#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>//atoi()
#include <iomanip>//for setw()

#include "ui/interface.h"
#include "services/service.h"
#include "models/computers.h"
#include "models/persons.h"
#include "repo/repository.h"

using namespace std;

InterFace::InterFace(){} //default constructor

void InterFace::runInterFace(){
        InterFace::displayMainMenu();
        InterFace::actionSelect();
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
          invalidInput();
          break;

      }
  }while(loop);

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
    cout << "Gender (f=female, m=male): ";
    do{
        cin >> gender;
        if(gender != "f" && gender != "F" && gender != "m" && gender != "M"){
            inputCheckVar.cinFailCheck();
        }
    }while(gender != "f" && gender != "F" && gender != "m" && gender != "M");

    //Get birth year input
    cout << "Year of birth: ";
    do{
        cin >> bYear;
    }while(!inputCheckVar.checkNumber(bYear, 1000, 2010));

    cout << "Year of death (0 if still alive): ";
    do{
        cin >> dYear;
    }while(dYear != 0 && !inputCheckVar.checkNumber(dYear, bYear+8, bYear+110));

    //Get input Known for info
    cout << "Is known for (\"0\" to skip): ";
    do{
        cin.ignore();
        getline(cin, knownFor);
        if((knownFor != "0") && (knownFor.length() < 3) )
            invalidInput();
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
    int yearBuilt = NULL;
    string cType = "";

    cout << "\n";
    cout << "Computer entry" << endl;
    cout << "Name: ";

    do{
        getline(cin, compName);
        if (compName.empty())
        {
            invalidInput();
            //cout << "Invalid input, reenter" << endl;
        }
    }while(compName.empty());

    cout << "Was it built (y/n): ";
    do{
        cin >> ifMade;
        if((ifMade.empty() || ifMade.length() > 1) || (ifMade != "y" && ifMade != "Y" && ifMade != "n" && ifMade !="N")){
            invalidInput();
        }else{
            wasItMade = 1;
        }
    }while((ifMade.empty() || ifMade.length() > 1) || (ifMade != "y" && ifMade != "Y" && ifMade != "n" && ifMade !="N"));

    if(wasItMade){
        cout << "When was the computer built: ";
        do{
            cin >> yearBuilt;
        }while(!inputCheckVar.checkNumber(yearBuilt, 1000, 2015));
    }

        cout << "What type of computer is it" << endl;;
        cout << "1: Mechanical" << endl;
        cout << "2: Electronic" << endl;
        cout << "3: Electro-Mechanical" << endl;
        cout << "4: Transistorized" << endl;
        cout << "choose: ";

        do{
            cin >> cType;
        }while(! inputCheckVar.isInputGood(1, 4, cType));

        if(cType == "1"){
            compType = "Mechanical";
        }else if(cType == "2"){
            compType = "Electronic";
        }else if(cType == "3"){
            compType = "Electro-Mechanical";
        }else if(cType == "4"){
            compType = "Transistorized";
        }

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
    int sortWith, order;
    string choice, var;
    vector<Persons> sortedList = serviceVar.getSortedPersonsList(1,0);
    int numberOfEnteries = sortedList.size(), personOfInterest;

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

    cout << endl;

    //morePersInfo();

    cout << "If you would like to see more information on each person, please choose a # (0 for cancel): ";
    do{
        cin >> var;
    } while(!inputCheckVar.isInputGood(0, numberOfEnteries, var));
    if(var == "0"){
        runInterFace();
    }
    //morePersInfo(sortedList.at(var));
    //morePersInfo();

    cout << endl << endl;

    //if (var)

  /*  cout << "1. Sort again" << endl;
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
    }*/
    runInterFace();
}

void InterFace::printDispCompMenu(){
    int sortWith, order, var;
    string choice, again;

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

    cout << endl << endl;
    printPerson( serviceVar.searchScient(searchS)  );

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


    cout << endl << endl;
    printComputers( serviceVar.searchComp(searchS)  );

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


void InterFace::morePersInfo(const Computers showComputer){



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
  cout << '\n' << setw(3) << left << "#"
       << setw(30) << "Name:" << setw(20) << "Type:" << setw(8) << "Built:"
       << "Year built:" << endl;
  for(unsigned int i = 0; i < compList.size(); i++){

      cout << setw(3)  << left << i+1;
      cout << setw(30) << left << compList.at(i).getName();
      cout << setw(20) << compList.at(i).getType();

      if(compList.at(i).getBuild()){
          cout << setw(8) << "Yes";}
      else{
          cout << setw(8) << "No";}

      if( NULL == (compList.at(i).getBuildYear()) )
          cout << "" << '\n';
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

    vector<Persons> sortedList = serviceVar.getSortedPersonsList(1,0);
    int enteryRemove, numberOfEnteries = sortedList.size(), var;
    string input;

    printPerson( sortedList );
    cout<< endl << "Which one of these enteries do you want to remove(select # / 0 for cancel)? ";

    do{
        cin >> input;
    }while( ! inputCheckVar.isInputGood(0, numberOfEnteries, input)   );
    enteryRemove = (atoi( input.c_str() ) ) -1;


    if( serviceVar.removePersEntery(enteryRemove, sortedList) )
      cout << endl << "Entry no longer visable in list" << endl << endl;
    else
      cout << endl << "Unable to delete" << endl << endl;

    cout << endl << endl;

    cout << "1. Remove something else from the list" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> input;
    } while(! inputCheckVar.isInputGood(1,2, input));
    var = atoi(input.c_str());

    if (var == 1){
        cout << endl << endl << endl;
        printRemoveMenu();
    } else if (var == 2){
        cout << endl << endl << endl;
        runInterFace();
    }
    runInterFace();
}

void InterFace::printRemoveCompMenu(){

  vector<Computers> sortedList = serviceVar.getSortedComputersList(1,0);
  int enteryRemove, numberOfEnteries = sortedList.size() ,  var;
  string input="";

  printComputers( sortedList );
  cout << endl << "Which one of these enteries do you want to remove(select # / 0 for cancel)? ";

  do{
      cin >> input;
  }while( ! inputCheckVar.isInputGood(0, numberOfEnteries, input)   );
  enteryRemove = atoi( input.c_str() ) -1;



  if( serviceVar.removeCompEntery(enteryRemove, sortedList) )
    cout << endl << "Entry no longer visable in list" << endl << endl;
  else
    cout << endl << "Unable to delete" << endl << endl;


  cout << "1. Remove something else from the list" << endl;
  cout << "2. Back to main menu" << endl;
  cout << "Enter choice: ";
  do{
      cin >> input;
  } while(! inputCheckVar.isInputGood(1,2, input));
  var = atoi(input.c_str());

  if (var == 1){
      cout << endl << endl << endl;
      printRemoveMenu();
  } else if (var == 2){
      cout << endl << endl << endl;
      runInterFace();
  }

}

void InterFace::invalidInput(){
  cout << "This input is not valid. Please try again: ";
}
