#include <vector>
#include <string>

#pragma once
using namespace std; 

class StorageDatabase{
	private:
		string fileName;
		static const int noOfTaskAttributes; 
	
	public:
		StorageDatabase(void);
		void writeToDatabase(vector<vector<string>> taskStringVectorToWrite);
		vector<vector<string>> readFromDatabase();
		vector<string> readFromDataBaseIndividualTaskString(); 
};

