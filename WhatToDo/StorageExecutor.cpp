#include "StorageExecutor.h"

using namespace std; 

StorageExecutor::StorageExecutor(void){
}

State StorageExecutor::loadFromStorage(){
	vector<Task> myConvertedTask;
	//get vector of strings from StorageDatabase
	storageToConvert = myStorageDatabase.readFromDatabase();
	//cannot read a null pointer
	
	assert(&storageToConvert != NULL);
	
	vector<vector<string>>::iterator myStorageIterator = storageToConvert.begin();
	
	//convert each string into task using storageConverterdddd
	while(myStorageIterator!=storageToConvert.end()){
		myIndividualTask = myStorageConverter.convertStringToTask(*myStorageIterator);
		myConvertedTask.push_back(myIndividualTask);
		myStorageIterator++;
	}

	//pack tasks into state and return as state
	vector<Task>::iterator taskIterator = myConvertedTask.begin();
	assert(&taskIterator!=NULL);

	while(taskIterator!= myConvertedTask.end()){
		stateToLoad.addTask(*taskIterator); 
		taskIterator++; 
	}

	return stateToLoad;
}

void StorageExecutor::saveToStorage(State stateToSave){
	//first get all task for a given State and returns a vector of Tasks
	vector<Task> taskToStore = stateToSave.getAllTasks(); 

	assert(&taskToStore != NULL);

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