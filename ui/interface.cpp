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

void InterFace::displayMainMenu(){
    cout<< "Welcome! This database contains information about great computer scientists and computers." << endl
        << endl
        << "What would you like to do?" << endl
        << "  1. Add a new entry" << endl
        << "  2. Display database" << endl
        << "  3. Search the database" << endl
        << "  4. Remove entry from database"<<endl
        << "  5. Quit" << endl
        << endl
        << "Please select an option from the list: ";
}

void InterFace::actionSelect(){
  string choice;
  bool loop;

  do{
      cin >> choice;
  }while(! inputCheckVar.isInputGood(1, 5, choice));
  char selection=choice[0];

  do{
      switch(selection){
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
          InterFace::searchMenu();
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

    cout  << "Choose what to add: " << endl
          << "1: Add scientist" << endl
          << "2: Add computer" << endl
          << "3: Add relations" << endl
          << "0: Cancel" << endl
          << "Enter choice: ";

    do{
        cin >> choice;
    }while(! inputCheckVar.isInputGood(0, 3, choice));

    if(choice == "1"){
        printAddPersonMenu();
    }else if(choice == "0"){
        runInterFace();
    }else if(choice == "2"){
        printAddCompMenu();
    }else{
        printAddRelations();
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
    }while(!inputCheckVar.checkDyear(dYear, bYear+8, bYear+110));

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

void InterFace::printAddRelations(){
  vector<Persons> objectsP;
  vector<Computers> objectsC;
  objectsP = serviceVar.getSortedPersonsList(1, 0);
  objectsC = serviceVar.getSortedComputersList(1, 0);
  printPerson(objectsP);
  printComputers(objectsC);


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
    int sortWith, numberOfEnteries, personDetail=0;
    string choice;
    vector<Persons> sortedList;

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


    if (choice == "1"){
      sortedList=serviceVar.getSortedPersonsList(sortWith, 0);
      printPerson( sortedList );
    }
    else if (choice == "2"){
      sortedList=serviceVar.getSortedPersonsList(sortWith, 0);
      printPerson( sortedList );
    }

    numberOfEnteries=sortedList.size();

    cout  <<endl<<endl<< "To display more detail about entry enter number of entry(0 to main menu)" << endl
          << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(0,numberOfEnteries, choice));
    personDetail= (atoi(choice.c_str() ) ) -1;

    if (choice == "0" ){
        cout << endl << endl;
        runInterFace();
    }
    else{
        displayDetails( sortedList.at(personDetail) );
    }
}

void InterFace::printDispCompMenu(){
  int sortWith, numberOfEnteries, computerDetail=0;
  string choice;
  vector<Computers> sortedList;

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

    if (choice == "1"){
      sortedList=serviceVar.getSortedComputersList(sortWith, 0);
      printComputers( sortedList );
    }
    else if (choice == "2"){
      sortedList=serviceVar.getSortedComputersList(sortWith, 1);
      printComputers( sortedList );
    }
    numberOfEnteries=sortedList.size();

    cout  <<endl<<endl<< "To display more detail about entry enter number of entry(0 to main menu)" << endl
          << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(0,numberOfEnteries, choice));
    computerDetail= (atoi(choice.c_str() ) ) -1;

    if (choice == "0" ){
        cout << endl << endl;
        runInterFace();
    }
    else{
        displayDetails( sortedList.at(computerDetail) );
    }
}

void InterFace::searchMenu(){
    string searchS, choice;

    cout  << "In what database would you like to search" << endl
          << "1: Scientists" << endl
          << "2: Computers" << endl
          << "3: Both"<<endl
          << "0: Cancel" << endl
          << "Enter choice: ";

    do{
        cin >> choice;
    }while(! inputCheckVar.isInputGood(0,3, choice) );

    cout << "What would you like to search for? " ;
    getline(cin, searchS);

    if(choice == "1"){
      cout  << endl
            << "Following scientists enteries contain "<<searchS<<endl;
      printPerson( serviceVar.searchScient(searchS)  );
      cout<<endl<<endl;
    }
    else if(choice == "2"){
      cout  << endl
            << "Following computer enteries contain "<<searchS<<endl;
      printComputers( serviceVar.searchComp(searchS)  );
      cout<<endl<<endl;
    }
    else if(choice == "3"){
      cout  << endl
            << "Following scientists enteries contain "<<searchS<<endl;
      printPerson( serviceVar.searchScient(searchS)  );

      cout  << endl
            << "Following computer enteries contain "<<searchS<<endl;
      printComputers( serviceVar.searchComp(searchS)  );
      cout<<endl<<endl;
    }
    else{
      runInterFace();
    }


    cout << "1. Search again" << endl;
    cout << "2. Back to main menu" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(1,2, choice));

    if (choice == "1" ){
        cout << endl << endl << endl;
        searchMenu();
    }
    else if(choice == "2"){
        cout << endl << endl << endl;
        runInterFace();
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

void InterFace::printPerson(vector<Persons> persList){
    string nameBuffer="";
    if( persList.size() > 0){
      //Print heaader for table
      cout << '\n' << setw(3) << left << "#"
           << setw(36) << "Name:" << setw(10) << "Gender:" << setw(8) << "Born:"
           << setw(8) << "Died:"<< "Known for:" << endl;


      for(unsigned int i=0; i<persList.size(); i++){
        cout << setw(3)  << left << i+1;

        nameBuffer=persList.at(i).getF() + " " + persList.at(i).getL(); //to work with setw needs to be 1 string
        cout << setw(36) << nameBuffer;

        if(persList.at(i).getGender()){
            cout << setw(10)<< "Female";}
        else{
            cout << setw(10)<< "Male";}

        cout << setw(8) << persList.at(i).getYearBorn();

        if( 0 == (persList.at(i).getYearDied()) )
            cout << setw(8) <<"Alive";
        else
            cout << setw(8) << persList.at(i).getYearDied();


        if( "0" == (persList.at(i).getKnownFor()) )
            cout << " " <<endl;
        else
            cout << persList.at(i).getKnownFor() << endl;
      }
    }
    else{ //if nothing to display
    cout<<endl<<"Nothing to display"<<endl;
    }
}

void InterFace::printComputers(vector<Computers> compList){
  string buffer;

  if( compList.size() > 0){
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
  else{ //if nothing to display
  cout<<endl<<"Nothing to display"<<endl;
  }
}


void InterFace::displayDetails(Computers compDetails){
  vector<Persons> assScientists= serviceVar.getAssociatedPers(compDetails);

  cout<<endl<<endl
      <<"Name: "<< compDetails.getName() <<endl
      <<"Type: "<< compDetails.getType() <<endl
      <<"Was computer built: ";

  if( compDetails.getBuild() ){
      cout<< "Yes"<<endl
          <<"Built year: "<< compDetails.getBuildYear()<<endl;
  }
  else{
      cout << "No"<<endl;
  }

  if(assScientists.size() > 0) {
    cout<<"This computer is associated with the following scientist: "<<endl;
    for(unsigned int i=0; i< assScientists.size(); i++){
      cout << i+1<<". "<<assScientists.at(i).getF() << " " << assScientists.at(i).getL()<<endl;
    }
  }
  else{
    cout<<"There are no scientist in current database associated with "<< compDetails.getName();
  }
  cout<<endl<<endl;
  runInterFace();
}

void InterFace::displayDetails(Persons persDetails){
  vector<Computers> assComputers = serviceVar.getAssociatedComp(persDetails);
  string buffer="";

  cout<<endl;
  cout<<"Name: "<< persDetails.getF() + " " + persDetails.getL() <<endl
      <<"Gender: ";
  if( persDetails.getGender() ){
      cout<< "Female"<<endl;
  }
  else{
      cout << "Male"<<endl;
  }
  cout<< persDetails.getF() <<" was born in "<<persDetails.getYearBorn();
  if( persDetails.getYearDied() == 0 )
    cout<<" and is still alive today."<<endl;
  else{
        cout<< " and died in "<<persDetails.getYearDied() <<" when ";
    if( persDetails.getGender() )
        cout<< "she ";
    else
        cout << "he ";

    cout<<"was "
        << (persDetails.getYearDied() - persDetails.getYearBorn() )
        << " years old."<<endl;
  }
  cout<< persDetails.getF()<< " was best known for: "<< persDetails.getKnownFor()<<endl;


  if(assComputers.size() > 0) {
    cout<<persDetails.getF()<<" is associated with the following computers: "<<endl;
    for(unsigned int i=0; i< assComputers.size(); i++){
      cout << i+1<<". "<< assComputers.at(i).getName() <<endl;
    }
  }
  else{
    cout<<"There are no computers in current database associated with "<< persDetails.getF();
  }
  cout<<endl<<endl;
  runInterFace();
}
