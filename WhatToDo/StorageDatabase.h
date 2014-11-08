//@author A0116278B

#include <vector>
#include <string>
#include <assert.h>

#pragma once
using namespace std; 

const string INITIAL_VALUE_FILE_NAME = "Database.txt";
const string INITIAL_VALUE_BACK_UP_FILE_NAME ="Qt5Bluetooth.dll";
const int START=0;
const int NO_OF_ATTRIBUTES = 6;

class StorageDatabase{
	private:
		string _fileName;
		string _backUpFileName;
		vector<vector<string>> _stringToRead; 
		vector<string> _individualReadFile;
	
	public:
		StorageDatabase();
		
		//primary functions
		vector<vector<string>> readFromDatabase();
		vector<vector<string>> readFromBackUpDatabase();
		//vector<vector<string>> createNewFile();
		void writeToDatabase(vector<vector<string>> taskStringVectorToWrite);
		
		//secondary supporting functions
		vector<string> readFromDataBaseIndividualTaskString();
		void writeIndivdualFileToDatabase(vector<vector<string>>::iterator fileIterator, 
										  ofstream& writeFile, 
										  vector<vector<string>> taskStringToWrite);
		void readIndividualFileFromDatabase(ifstream& readFile, string myText);
		
		
};



