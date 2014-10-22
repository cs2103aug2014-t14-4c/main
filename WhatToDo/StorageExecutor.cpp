#include "StorageExecutor.h"

using namespace std; 

StorageExecutor::StorageExecutor(void){
}

State StorageExecutor::loadFromStorage(){
	
	//get vector of strings from StorageDatabase
	storageToConvert = myStorageDatabase.readFromDatabase();
	
	assert(&storageToConvert != NULL);
	//cannot read a null pointer
	
	vector<vector<string>>::iterator myStorageIterator = storageToConvert.begin();
	
	//convert each string into task using storageConverterdddd
	processVectorToTaskConversion(myStorageIterator);

	//pack tasks into state and return as state
	vector<Task>::iterator taskIterator = myConvertedTask.begin();
	assert(&taskIterator!=NULL);
	stateToLoad = processTaskAddition(taskIterator);

	return stateToLoad;
}

void StorageExecutor::saveToStorage(State stateToSave){
	//first get all task for a given State and returns a vector of Tasks
	taskToStore = stateToSave.getAllTasks(); 

	assert(&taskToStore != NULL);

	//for each task, convert to string using string converter
	vector<Task>::iterator myTaskIterator = taskToStore.begin();
	convertAllTaskToString(myTaskIterator);
	//send to StorageDatabase for writing of file
	myStorageDatabase.writeToDatabase(convertedTaskStringStorage);
	
	return;
}

void StorageExecutor::processVectorToTaskConversion(vector<vector<string>>::iterator vIterator){
	//convert string to task
	while(vIterator!=storageToConvert.end()){
		myIndividualTask = myStorageConverter.convertStringToTask(*vIterator);
		myConvertedTask.push_back(myIndividualTask);
		vIterator++;
	}
	return;
}

State StorageExecutor::processTaskAddition(vector<Task>::iterator taskIterator){
	State stateToLoad;
	//adding task for loading by state
	while(taskIterator!= myConvertedTask.end()){
		stateToLoad.addTask(*taskIterator); 
		taskIterator++; 
	}
	return stateToLoad;
}

void StorageExecutor::convertAllTaskToString(vector<Task>::iterator taskIterator){

		while(taskIterator!=taskToStore.end()){
		individualConvertedTask = myStorageConverter.convertTaskToString(*taskIterator);
		//store the converted string into a vector of strings
		convertedTaskStringStorage.push_back(individualConvertedTask);
		taskIterator++;
	}

	return;
}