#include "StorageExecutor.h"

using namespace std; 

StorageExecutor::StorageExecutor(void){
}

State StorageExecutor::loadFromStorage(){
	State stateToLoad; 
	vector<vector<string>> storageToConvert; 
	vector<Task> myConvertedTask; 
	myConvertedTask.clear();
	StorageDatabase myStorageDatabase; 
	Task myIndividualTask; 
	StorageConverter myStorageConverter; 

	//get vector of strings from StorageDatabase
	storageToConvert = myStorageDatabase.readFromDatabase();
	vector<vector<string>>::iterator myStorageIterator = storageToConvert.begin();
	//convert each string into task using storageConverter
	while(myStorageIterator!=storageToConvert.end()){
		myIndividualTask = myStorageConverter.convertStringToTask(*myStorageIterator);
		myConvertedTask.push_back(myIndividualTask);
		myStorageIterator++;
	}

	//pack tasks into state and return as state
	stateToLoad.setAllTasks(myConvertedTask);

	return stateToLoad;
}

void StorageExecutor::saveToStorage(State stateToSave){

	StorageDatabase myStorageDatabase;
	StorageConverter myStorageConverter; 
	vector<vector<string>> convertedTaskStringStorage; 
	vector<string> individualConvertedTask;
	//first get all task for a given State and returns a vector of Tasks
	vector<Task> taskToStore = stateToSave.getAllTasks(); 
	//for each task, convert to string using string converter
	vector<Task>::iterator myTaskIterator = taskToStore.begin();

	while(myTaskIterator!=taskToStore.end()){
		individualConvertedTask = myStorageConverter.convertTaskToString(*myTaskIterator);
		//store the converted string into a vector of strings
		convertedTaskStringStorage.push_back(individualConvertedTask);
		myTaskIterator++;
	}
	//send to StorageDatabase for writing of file
	myStorageDatabase.writeToDatabase(convertedTaskStringStorage);
	
	return;
}