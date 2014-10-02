#include <vector>
#include <string>

#pragma once
using namespace std; 

class StorageDatabase{
	private:
		string fileName;
	
	public:
		StorageDatabase(void);
		void writeToDatabase(vector<string> stringToWrite);
		vector<string> readFromDatabase();
};

