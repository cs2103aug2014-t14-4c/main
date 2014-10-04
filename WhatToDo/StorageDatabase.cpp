#include "StorageDatabase.h"
#include <fstream>
using namespace std;

StorageDatabase::StorageDatabase(void){
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

vector<vector<string>> StorageDatabase::readFromDatabase(){

	//logic: check if works 
	//1. check no of attributes for each task
	//2. ifstream to getline the amount of attributes to store in the vector<string>
	//3. push the vector<string> into the vector of vectors
	vector<vector<string>> stringToRead; 
	vector<string> individualReadFile;
	int noOfTaskAttribute = 8;
	ifstream readFile(fileName);
	string myText; 

	while(getline(readFile,myText)){
		for(int i = 0; i<noOfTaskAttribute; i++){
			getline(readFile,myText);
			individualReadFile.push_back(myText);
		//GO TO THE NEXT LINE 
		}
		stringToRead.push_back(individualReadFile);
		individualReadFile.clear();
	}
	readFile.close();
	//how toooo readd??????

	return stringToRead; 
}

//vector<string> StorageDatabase::readFromDataBaseIndividualTaskString(){
//	vector<string> myIndivdualTaskVectorString; 
//	int noOfAttribute = 8;
//	string myText; 
//
//	ifstream readFile(fileName); 
//	for(int i = 0; i<noOfAttribute; i++){
//		getline(readFile,myText);
//		myIndivdualTaskVectorString.push_back(myText);
//		//GO TO THE NEXT LINE 
//	}
//	return myIndivdualTaskVectorString; 
//}

