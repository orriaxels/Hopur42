#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "repository.h"
#include "persons.h"

Repository::Repository(){
    //default construct
}


void Repository::readFile(){
    
    Persons Per;
    
    ifstream inFile;
    inFile.open("itpersons.txt");

    if ((inFile.fail())){        
        cout << endl<<endl<< "File failed to open";
    } 

    string lineString;

    while( (getline(inFile, lineString) )){

        if(1){ 
        vector<string> subStrings;
        stringstream inStream;
        inStream.str(lineString);
        unsigned int dateStart=0;
        string buffer="";

       //Reads line word by word into vector
        while (inStream >> buffer){
            if(buffer=="-1")
                break;
            subStrings.push_back(buffer);
        }

        //Find if name length is longer than two
        do{
            buffer=subStrings.at(dateStart);
            dateStart++;
        }while(isdigit(buffer[0]));

        //read in first name. For loop if fName is more than one word
        for(unsigned int i=0 ; i<dateStart-1; i++){
            buffer+=subStrings.at(i);
        }
        Per.setFirst(buffer);
        buffer=""; //clear buffer for use later

        //Sets last name
        Per.setLast(subStrings.at(dateStart));
        dateStart++;

        //reads gender into the person
        Per.setGender( convertToInt(subStrings.at(dateStart)) );//
        dateStart++;

        //reads year born from file
        Per.setBorn( convertToInt(subStrings.at(dateStart)) );
        dateStart++;

        Per.setDied( convertToInt(subStrings.at(dateStart)) );
        dateStart++;
//qoute code
//        for(dateStart; dateStart<subStrings.size(); dateStart++){
//            buffer+=subStrings.at(dateStart);
//            buffer+=" ";
//        }
           
        Per.setQuote(buffer);
        list.push_back(Per);
        } 
    }
    inFile.close();
}

int Repository::convertToInt(string strConvert){
    int num;
    if ( !(istringstream(strConvert) >> num) )
        num = 0;
    return num;
}


void Repository::writeToFile(Persons newPerson){
    ofstream toFile;
    toFile.open("itpersons.txt", ios::app); //app  append, or end of file

    toFile  << newPerson.getF() << " "
            << newPerson.getL() << " "
            << newPerson.getGender() << " "
            << newPerson.getYearBorn() << " "
            << newPerson.getYearDied() << " "
            << newPerson.getQuote() << " ";

    toFile.close();
}

vector<Persons> Repository::getList(){
    readFile();
    return list;
}
