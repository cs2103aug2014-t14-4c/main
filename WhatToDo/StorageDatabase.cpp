//@author A0116278B
#include "StorageDatabase.h"
#include <fstream>
#include <iostream>

using namespace std;

StorageDatabase::StorageDatabase(){
	_fileName = INITIAL_VALUE_FILE_NAME;
	_backUpFileName = INITIAL_VALUE_BACK_UP_FILE_NAME;
	_stringToRead.clear();

}

//1. check no of attributes for each task
//2. ifstream to getline the amount of attributes to store in the vector<string>
//3. push the vector<string> into the vector of vectors
vector<vector<string>> StorageDatabase::readFromDatabase(){

	ifstream readFile(_fileName);
	assert(&readFile!=NULL);
	string myText; 
	readIndividualFileFromDatabase(readFile, myText);
	readFile.close();

	return _stringToRead; 
}

//read from backup database if the database is corrupted 
vector<vector<string>> StorageDatabase::readFromBackUpDatabase(){

	ifstream readFile(_backUpFileName);
	assert(&readFile!=NULL);
	string myText; 
	readIndividualFileFromDatabase(readFile, myText);
	readFile.close();

	return _stringToRead; 
}

//pass in a vector<vector<string>> where each vector<string> is a task in vector<string> 
//form, the strings are then stored into both the database and backup database 
void StorageDatabase::writeToDatabase(vector<vector<string>> taskStringVectorToWrite){
	
	vector<vector<string>>::iterator taskVectorIterator = taskStringVectorToWrite.begin(); 
	assert(&taskVectorIterator != NULL);
	ofstream writeFile;

	writeFile.open(_fileName);
	assert(&writeFile!=NULL);
	writeIndivdualFileToDatabase(taskVectorIterator, writeFile, taskStringVectorToWrite);
	writeFile.close();

	taskVectorIterator = taskStringVectorToWrite.begin(); 
	assert(&writeFile != NULL);
	writeFile.open(_backUpFileName);
	writeIndivdualFileToDatabase(taskVectorIterator, writeFile, taskStringVectorToWrite); 

	writeFile.close(); 
	return;
}

void StorageDatabase::setFileName(string nameToSet){
	_fileName = nameToSet;
}

string StorageDatabase::getFileName(){
	return _fileName; 
}

//writing individual tasks after been converted to be stored into database
void StorageDatabase::writeIndivdualFileToDatabase(vector<vector<string>>::iterator fileIterator, 
													ofstream& writeFile, 
													vector<vector<string>> taskStringToWrite){
	
	fileIterator = taskStringToWrite.begin();
	while(fileIterator != taskStringToWrite.end()){
		for(int i = START; i < NO_OF_ATTRIBUTES; i++){
			writeFile << (*fileIterator)[i] << endl;
		}
		writeFile << endl; 
		fileIterator++;
	}
	return;
}

//database is read and after that the strings will be pushed back to a _stringToLoad
//vector where it is ready to be processed after all the strings are read and
//processed
void StorageDatabase::readIndividualFileFromDatabase(ifstream &readFile, string myText){
	
	_individualReadFile.clear();
	_stringToRead.clear();
	while(readFile.peek()!=EOF){
		for(int i = START; i < NO_OF_ATTRIBUTES; i++){
			getline(readFile,myText);
			_individualReadFile.push_back(myText);
		}

		getline(readFile,myText);
		_stringToRead.push_back(_individualReadFile);
		//clear to be ready for the next vector<string>
		_individualReadFile.clear();
	}
	return;
}

