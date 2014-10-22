#include <vector>
#include <string>
#include <assert.h>

#pragma once
using namespace std; 

class StorageDatabase{
	private:
		string fileName;
		vector<vector<string>> stringToRead; 
		vector<string> individualReadFile;
		static const int noOfTaskAttributes; 
	
	public:
		static int START;
		static int NO_OF_ATTRIBUTES;
		StorageDatabase();
		
		//primary functions
		vector<vector<string>> readFromDatabase();
		void writeToDatabase(vector<vector<string>> taskStringVectorToWrite);
		
		//secondary supporting functions
		vector<string> readFromDataBaseIndividualTaskString();
		void StorageDatabase::writeIndivdualFileToDatabase(vector<vector<string>>::iterator fileIterator, ofstream writeFile, vector<vector<string>> taskStringToWrite);
};



