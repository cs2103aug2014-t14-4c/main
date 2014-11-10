//@author A0116278B
//****************************************************************************
//StorageDatabase is the class responsible for reading and writing of file
//to Database. Files will be saved as .txt file format in local database 
//such that the user can directly edit the .txt file even before openning the
//programme. 

//StorageDatabase comprises of 2 main functions which are
//1)read from database 
//2)write to database 
//StorageDatabase also writes a copy of the schedule to a backup database
//in the event that the user accidentally deleted the database or corrupted
//the file that deem it unreadable. The user would however, be refrained from
//editting the backup copy.

//sample usage:
//storageDatabaseObj.writeToDatabase();
//vector<vector<string>> databaseString = StorageDatabaseObj.readFromDatabase();
//****************************************************************************

#include <vector>
#include <string>
#include <assert.h>

#pragma once
using namespace std;

const string INITIAL_VALUE_FILE_NAME = "Database.txt";
const string INITIAL_VALUE_BACK_UP_FILE_NAME ="BackupDatabase.bak";
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
		void writeToDatabase(vector<vector<string>> taskStringVectorToWrite);
		
		//secondary supporting functions
		void setFileName(string nameToSet); 
		string getFileName(); 
		vector<string> readFromDataBaseIndividualTaskString();
		void writeIndivdualFileToDatabase(vector<vector<string>>::iterator fileIterator, 
										  ofstream& writeFile, 
										  vector<vector<string>> taskStringToWrite);
		void readIndividualFileFromDatabase(ifstream& readFile, string myText);
		
		
};



