#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "repository.h"
#include "persons.h"

Repository::Repository()
{
}


void Repository::readFile(){

    stringstream lineIn;
    ifstream inFile;
    inFile.open("noteworthyPersons.txt");

    string lineString;

    while( getline(inFile, lineString) ){

        lineIn.str(lineString);
        vector<string> subStrings;
        unsigned int dateStart=0;
        Persons Per;
        string buffer="";

        while( lineIn.good() ){
            string word="";
            lineIn >> word;

            subStrings.push_back(word);
        }

        //Find if name length is longer than two
        do{
            buffer=subStrings.at(dateStart);
            dateStart++;
        }while(isdigit(buffer[0]));

        //read in first name
        for(unsigned int i=0 ; i<dateStart-1; i++){
            buffer+=subStrings.at(i);
        }
        Per.setFirst(buffer);
        buffer=""; //clear buffer for use later
        Per.setLast(subStrings.at(dateStart-1));


        Per.setGender( convertToInt(subStrings.at(dateStart)) );
        dateStart++;

        Per.setBorn( convertToInt(subStrings.at(dateStart)) );
        dateStart++;

        Per.setDied( convertToInt(subStrings.at(dateStart)) );
        dateStart++;

        for(dateStart; dateStart<subStrings.size(); dateStart++){
            buffer+=subStrings.at(dateStart);
            buffer+=" ";
        }
        Per.setQuote(buffer);
        list.push_back(Per);
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
    toFile.open("noteworthyPersons.txt", ios::app); //app  append, or end of file

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
