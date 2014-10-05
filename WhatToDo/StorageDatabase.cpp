#include "StorageDatabase.h"
#include <fstream>
using namespace std;
const int StorageDatabase::noOfTaskAttributes=7;

StorageDatabase::StorageDatabase(void){
}

void StorageDatabase::writeToDatabase(vector<vector<string>> taskStringVectorToWrite){
	
	vector<vector<string>>::iterator taskVectorIterator = taskStringVectorToWrite.begin(); 
	
	ofstream writeFile;
	writeFile.open(fileName);

	while(taskVectorIterator != taskStringVectorToWrite.end()){
		for(int i = 0; i< noOfTaskAttributes; i++){
			writeFile << (*taskVectorIterator)[i] << endl;
		}
		taskVectorIterator++;
	}

	writeFile.close();
	return;
}

vector<vector<string>> StorageDatabase::readFromDatabase(){

	//logic: check if works 
	//1. check no of attributes for each task
	//2. ifstream to getline the amount of attributes to store in the vector<string>
	//3. push the vector<string> into the vector of vectors
	vector<vector<string>> stringToRead; 
	vector<string> individualReadFile;
	ifstream readFile(fileName);
	string myText; 

	while(readFile.peek()!=EOF){
		for(int i = 0; i<noOfTaskAttributes; i++){
			getline(readFile,myText);
			individualReadFile.push_back(myText);
		//GO TO THE NEXT LINE 
		}
		stringToRead.push_back(individualReadFile);
		//clear to be ready for the next vector<string>
		individualReadFile.clear();
	}
	readFile.close();
	//how toooo readd??????

	return stringToRead; 
}
