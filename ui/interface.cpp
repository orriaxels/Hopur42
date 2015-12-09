#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>//atoi()
#include <iomanip>//for setw()

#include "ui/interface.h"
#include "services/service.h"
#include "models/computer.h"
#include "models/scientist.h"

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
          InterFace::addMenu();
          break;
      case '2':
          cout << endl;
          InterFace::displayMenu();
          break;
      case '3':
          cout << endl;
          InterFace::searchMenu();
          break;
      case '4':
          cout<<endl;
          InterFace::removeMenu();
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

void InterFace::addMenu(){
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
        addScientistMenu();
    }else if(choice == "0"){
        runInterFace();
    }else if(choice == "2"){
        addCompMenu();
    }else{
        addRelations();
    }

}

void InterFace::addScientistMenu(){

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



    if( serviceVar.createScientist(name, gender, bYear, dYear, knownFor) )
      cout<<endl<<"Entry sucsessfully added to database"<<endl<<endl<<endl;
    else
      cout<<endl<<"Unable to write to database"<<endl<<endl<<endl;

    runInterFace();
}

void InterFace::addCompMenu(){

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

void InterFace::addRelations(){
  vector<Scientist> allScientist=serviceVar.getSortedScientistList(1, 0);;
  vector<Computer> allComputers= serviceVar.getSortedComputerList(1, 0);
  string choice;
  int sizeVector=allScientist.size(), indexScie=0, indexComp=0;

  printScientist(allScientist);
  cout  <<endl<< "Select Scientist to add relation to(0 to main menu)" << endl
        << "Enter choice: ";
  do{
      cin >> choice;
  }while(! inputCheckVar.isInputGood(0,sizeVector+1, choice));
  indexScie=( atoi(choice.c_str() ) ) -1;

  if (choice == "0" ){
      cout << endl << endl;
      runInterFace();
  }

  sizeVector=allComputers.size();
  printComputers(allComputers);
  cout  <<endl<< "Select computer to add relation to "<< (allScientist.at(indexScie)).getF()<<" (0 to main menu)" << endl
        << "Enter choice: ";
  do{
      cin >> choice;
  }while(! inputCheckVar.isInputGood(0,sizeVector+1, choice));
  indexComp=atoi(choice.c_str() ) -1;

  if (choice == "0" ){
      cout << endl << endl;
      runInterFace();
  }
  if( serviceVar.createRelation( allComputers.at(indexComp) , allScientist.at(indexScie) ) ){
    cout<<endl<<"Relation between "<< (allScientist.at(indexScie)).getF()<< " and "
        << (allComputers.at(indexComp)).getName() << " sucsessfully created."<<endl<<endl;
  }
  else
    cout<<endl<<"Unable to create relation"<<endl;

  runInterFace();
}

void InterFace::displayMenu(){
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
        dispScientistMenu();
    }else if(choice == "0"){
        runInterFace();
    }else{
        dispCompMenu();
    }
}

void InterFace::dispScientistMenu(){
    int sortWith, numberOfEnteries, scientistDetail=0;
    string choice;
    vector<Scientist> sortedList;

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
      sortedList=serviceVar.getSortedScientistList(sortWith, 0);
      printScientist( sortedList );
    }
    else if (choice == "2"){
      sortedList=serviceVar.getSortedScientistList(sortWith, 0);
      printScientist( sortedList );
    }

    numberOfEnteries=sortedList.size();

    cout  <<endl<<endl<< "To display more detail about entry enter number of entry(0 to main menu)" << endl
          << "Enter choice: ";
    do{
        cin >> choice;
    } while(! inputCheckVar.isInputGood(0,numberOfEnteries, choice));
    scientistDetail= (atoi(choice.c_str() ) ) -1;

    if (choice == "0" ){
        cout << endl << endl;
        runInterFace();
    }
    else{
        displayDetails( sortedList.at(scientistDetail) );
    }
}

void InterFace::dispCompMenu(){
  int sortWith, numberOfEnteries, computerDetail=0;
  string choice;
  vector<Computer> sortedList;

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
      sortedList=serviceVar.getSortedComputerList(sortWith, 0);
      printComputers( sortedList );
    }
    else if (choice == "2"){
      sortedList=serviceVar.getSortedComputerList(sortWith, 1);
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
      printScientist( serviceVar.searchScient(searchS)  );
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
      printScientist( serviceVar.searchScient(searchS)  );

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

void InterFace::removeMenu(){
    string choice;


    cout << "In what database would you like to remove data" << endl;
    cout << "1: Scientists" << endl;
    cout << "2: Computers" << endl;
    cout << "3: Relations" << endl;
    cout << "0: Cancel" << endl;
    cout << "Enter choice: ";
    do{
        cin >> choice;
    }while(! inputCheckVar.isInputGood(0,3, choice) );

    if(choice == "1"){
        removeScienMenu();
    }
    else if(choice == "2"){
        removeCompMenu();
    }
    else if(choice == "3"){
        removeRelation();
    }
    else
        runInterFace();

}

void InterFace::removeScienMenu(){

    vector<Scientist> sortedList = serviceVar.getSortedScientistList(1,0);
    int enteryRemove, numberOfEnteries = sortedList.size(), var;
    string input;

    printScientist( sortedList );
    cout<< endl << "Which one of these enteries do you want to remove(select # / 0 for cancel)? ";

    do{
        cin >> input;
    }while( ! inputCheckVar.isInputGood(0, numberOfEnteries, input)   );
    enteryRemove = (atoi( input.c_str() ) ) -1;


    if( serviceVar.removeScientEntery(enteryRemove, sortedList) )
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
        removeMenu();
    } else if (var == 2){
        cout << endl << endl << endl;
        runInterFace();
    }
    runInterFace();
}

void InterFace::removeCompMenu(){

  vector<Computer> sortedList = serviceVar.getSortedComputerList(1,0);
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
      removeMenu();
  } else if (var == 2){
      cout << endl << endl << endl;
      runInterFace();
  }

}

void InterFace::removeRelation(){
  vector<Scientist> scientSorted= serviceVar.getSortedScientistList(1,0);
  vector<Computer> compSorted= serviceVar.getSortedComputerList(1,0);
  vector<Computer> bufferComp;
  string choice;
  int indexTable=1, indexChoosen;
  vector<int> idContainer;
  cout<<endl<<"Here is a list of current relation in database:"<<endl;
  for(unsigned int i=0; i< scientSorted.size(); i++){
    bufferComp= serviceVar.getAssociatedComp(scientSorted.at(i));
    if(bufferComp.size() >0 )
      for(unsigned int j=0; j<bufferComp.size(); j++){
        idContainer.push_back( (scientSorted.at(i)).getId() );
        idContainer.push_back( (bufferComp.at(j)).getId() );

        string bufferName=(scientSorted.at(i)).getF() + " " + (scientSorted.at(i)).getL(); //setw needs one variable to behave
        cout<< setw(3)<<left<< indexTable++ <<bufferName;

        cout<<"-=-"<<(bufferComp.at(j)).getName()<<endl;
      }
  }
  cout<<endl<<"Which one of these relation do you want to remove(0 to Main menu): ";
  do{
      cin >> choice;
  }while(! inputCheckVar.isInputGood(0,indexTable, choice) );
  indexChoosen=atoi(choice.c_str() );

  if(choice=="0"){
    runInterFace();
  }
  else{
    indexChoosen=(indexChoosen-1)*2;
    cout<<endl<<"===ID SCIE"<< idContainer.at(indexChoosen)
        <<endl<<"===ID COMP"<< idContainer.at(indexChoosen+1);

    if( serviceVar.removeRelation( idContainer.at(indexChoosen), idContainer.at(indexChoosen+1) ) )
      cout<<endl<<"Relation sucsessfully removed."<<endl;
    else
      cout<<endl<<"Unable to remove relation"<<endl;
  }

  runInterFace();
}

void InterFace::invalidInput(){
  cout << "This input is not valid. Please try again: ";
}

void InterFace::printScientist(vector<Scientist> scientistList){
    string nameBuffer="";
    if( scientistList.size() > 0){
      //Print heaader for table
      cout << '\n' << setw(3) << left << "#"
           << setw(36) << "Name:" << setw(10) << "Gender:" << setw(8) << "Born:"
           << setw(8) << "Died:"<< "Known for:" << endl;


      for(unsigned int i=0; i<scientistList.size(); i++){
        cout << setw(3)  << left << i+1;

        nameBuffer=scientistList.at(i).getF() + " " + scientistList.at(i).getL(); //to work with setw needs to be 1 string
        cout << setw(36) << nameBuffer;

        if(scientistList.at(i).getGender()){
            cout << setw(10)<< "Female";}
        else{
            cout << setw(10)<< "Male";}

        cout << setw(8) << scientistList.at(i).getYearBorn();

        if( 0 == (scientistList.at(i).getYearDied()) )
            cout << setw(8) <<"Alive";
        else
            cout << setw(8) << scientistList.at(i).getYearDied();


        if( "0" == (scientistList.at(i).getKnownFor()) )
            cout << " " <<endl;
        else
            cout << scientistList.at(i).getKnownFor() << endl;
      }
    }
    else{ //if nothing to display
    cout<<endl<<"Nothing to display"<<endl;
    }
}

void InterFace::printComputers(vector<Computer> compList){
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

void InterFace::displayDetails(Computer compDetails){
  vector<Scientist> assScientists= serviceVar.getAssociatedScient(compDetails);

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

void InterFace::displayDetails(Scientist scientistDetails){
  vector<Computer> assComputers = serviceVar.getAssociatedComp(scientistDetails);
  string buffer="";

  cout<<endl;
  cout<<"Name: "<< scientistDetails.getF() + " " + scientistDetails.getL() <<endl
      <<"Gender: ";
  if( scientistDetails.getGender() ){
      cout<< "Female"<<endl;
  }
  else{
      cout << "Male"<<endl;
  }
  cout<< scientistDetails.getF() <<" was born in "<<scientistDetails.getYearBorn();
  if( scientistDetails.getYearDied() == 0 )
    cout<<" and is still alive today."<<endl;
  else{
        cout<< " and died in "<<scientistDetails.getYearDied() <<" when ";
    if( scientistDetails.getGender() )
        cout<< "she ";
    else
        cout << "he ";

    cout<<"was "
        << (scientistDetails.getYearDied() - scientistDetails.getYearBorn() )
        << " years old."<<endl;
  }
  cout<< scientistDetails.getF()<< " was best known for: "<< scientistDetails.getKnownFor()<<endl;


  if(assComputers.size() > 0) {
    cout<<scientistDetails.getF()<<" is associated with the following computers: "<<endl;
    for(unsigned int i=0; i< assComputers.size(); i++){
      cout << i+1<<". "<< assComputers.at(i).getName() <<endl;
    }
  }
  else{
    cout<<"There are no computers in current database associated with "<< scientistDetails.getF();
  }
  cout<<endl<<endl;
  runInterFace();
}
