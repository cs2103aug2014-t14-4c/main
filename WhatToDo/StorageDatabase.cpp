#include "StorageDatabase.h"
#include <fstream>
#include <iostream>
using namespace std;

StorageDatabase::StorageDatabase(){
	fileName = "integrate2.txt";
}
int StorageDatabase::START=0;
int StorageDatabase::NO_OF_ATTRIBUTES = 6;


//pass in a vector<vector<string>> where each vector<string> is a task in vector<string> form
void StorageDatabase::writeToDatabase(vector<vector<string>> taskStringVectorToWrite){
	
	vector<vector<string>>::iterator taskVectorIterator = taskStringVectorToWrite.begin(); 
	assert(&taskVectorIterator != NULL);
	
	ofstream writeFile;
	writeFile.open(fileName);

	try{
		//note that can be created as a function so can test elsewhere in programme
		if(NO_OF_ATTRIBUTES < 6){
			throw 1;
		}
		if(NO_OF_ATTRIBUTES >6){
			throw 2;
		}
	}catch(int errorCode){
		if(errorCode == 1){
			cout << "number of attributes less than 6!!" << endl;
		}
		if(errorCode ==2){
			cout << "number of attributes more than 6!" << endl;
		}
	}

	//write individual task attributes
	while(taskVectorIterator != taskStringVectorToWrite.end()){
		for(int i = START; i< NO_OF_ATTRIBUTES; i++){
			writeFile << (*taskVectorIterator)[i] << endl;
		}
		writeFile << endl; 
		taskVectorIterator++;
	}

	writeFile.close();
	return;
}

//logic:
//1. check no of attributes for each task
//2. ifstream to getline the amount of attributes to store in the vector<string>
//3. push the vector<string> into the vector of vectors
vector<vector<string>> StorageDatabase::readFromDatabase(){

	vector<vector<string>> stringToRead; 
	vector<string> individualReadFile;
	ifstream readFile(fileName);
	string myText; 
	
	//if peek != end of file, it will getline to read in the indvidual strings
	while(readFile.peek()!=EOF){
		for(int i = START; i<NO_OF_ATTRIBUTES; i++){
			getline(readFile,myText);
			individualReadFile.push_back(myText);
		}
		//read newline character
		getline(readFile,myText);
		stringToRead.push_back(individualReadFile);
		//clear to be ready for the next vector<string>
		individualReadFile.clear();
		assert(individualReadFile.empty());
	}
	readFile.close();

	return stringToRead; 
}
