#include "StorageDatabase.h"
#include <fstream>
using namespace std;

StorageDatabase::StorageDatabase(void)
{
}

void StorageDatabase::writeToDatabase(vector<string> stringToWrite){
	vector<string>::iterator myStringIterator = stringToWrite.begin(); 
	ofstream writeFile;
	writeFile.open(fileName, ios_base::app);
	while(myStringIterator != stringToWrite.end()){
		writeFile << *myStringIterator << endl; 
		myStringIterator++;
	}
	writeFile.close();
	return;
}

vector<string> StorageDatabase::readFromDatabase(){
	vector<string> stringToRead;
	string myText;
	ifstream readFile(fileName);
	while(getline(readFile, myText)){
		stringToRead.push_back(myText);
	}
	readFile.close();
	return stringToRead; 
}