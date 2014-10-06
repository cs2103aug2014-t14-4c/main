#pragma once
#include <vector>
#include <string>
using namespace std;

class StorageDatabase {
	public:
		StorageDatabase(void);
		void writeToDatabase(vector<string> stringToWrite);
		vector<string>readFromDatabase();

	private:

};

