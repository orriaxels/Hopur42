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
                subStrings.push_back(buffer);
            }

            //finds first element containing number(0 or 1 in this case)
            for(unsigned int i=0; i<subStrings.size();i++){
                buffer=subStrings.at(i);
                if((isdigit(buffer[0])) ){
                    buffer="";
                    break;
                }
                else{
                    dateStart++;
                }
            }

            if(dateStart==1){
                Per.setFirst(subStrings.at(0));
                Per.setLast("");
            }
            else{ 
                //read in first name. For loop if fName is more than one word
                for(unsigned int i=0 ; i<dateStart-1; ++i){
                    buffer+=subStrings.at(i);
                    if(i<(dateStart-2))
                        buffer+=" ";
                }
                Per.setFirst(buffer);
                buffer=""; //clear buffer for use later

                //Sets last name
                Per.setLast(subStrings.at(dateStart-1));
            }

            //reads gender into the person
            Per.setGender( convertToInt(subStrings.at(dateStart)) );//
            dateStart++;

            //reads year born from file
            Per.setBorn( convertToInt(subStrings.at(dateStart)) );
            dateStart++;

            Per.setDied( convertToInt(subStrings.at(dateStart)) );
            dateStart++;
            

           for(dateStart; dateStart < subStrings.size(); dateStart++){
               buffer+=subStrings.at(dateStart);
               buffer+=" ";
            }
               
            Per.setKnownFor(buffer);
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
            << newPerson.getKnownFor() << " "<<endl;

    toFile.close();
}


void Repository::backupList(vector<Persons> listBackup){
    ofstream backup;
    backup.open("backup_itPersons.txt", ofstream::trunc);

    for(unsigned int i=0; i<listBackup.size(); i++)
    backup  << listBackup.at(i).getF() << " "
            << listBackup.at(i).getL() << " "
            << listBackup.at(i).getGender() << " "
            << listBackup.at(i).getYearBorn() << " "
            << listBackup.at(i).getYearDied() << " "
            << listBackup.at(i).getKnownFor() << " "<<endl;

    backup.close();

}

void Repository::rewriteList(vector<Persons> listnew){
    ofstream backup;
    backup.open("itPersons.txt", ofstream::trunc);

    for(unsigned int i=0; i<listnew.size(); i++)
    backup  << listnew.at(i).getF() << " "
            << listnew.at(i).getL() << " "
            << listnew.at(i).getGender() << " "
            << listnew.at(i).getYearBorn() << " "
            << listnew.at(i).getYearDied() << " "
            << listnew.at(i).getKnownFor() << " "<<endl;

    backup.close();
}


vector<Persons> Repository::getList(){
    readFile();
    return list;
}
