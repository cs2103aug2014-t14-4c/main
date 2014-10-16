#include <vector>
#include <string>
#include <assert.h>

#pragma once
using namespace std; 

class StorageDatabase{
	private:
		string fileName;
		static const int noOfTaskAttributes; 
	
	public:
		StorageDatabase();
		static int START;
		static int NO_OF_ATTRIBUTES;
		void writeToDatabase(vector<vector<string>> taskStringVectorToWrite);
		vector<vector<string>> readFromDatabase();
		vector<string> readFromDataBaseIndividualTaskString(); 
};



