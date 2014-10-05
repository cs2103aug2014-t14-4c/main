#include "StorageExecutor.h"
#include "State.h"
#include "StorageConverter.h"
#include "StorageDatabase.h"
#include "Task.h"
using namespace std; 

StorageExecutor::StorageExecutor(void){
}

State StorageExecutor::loadFromStorage(){
	State stateToLoad; 
	vector<vector<string>> storageToConvert; 
	vector<Task> myConvertedTask; 
	StorageDatabase myStorageDatabase; 
	Task myIndividualTask; 
	StorageConverter myStorageConverter; 

	//get vector of strings from StorageDatabase--> do you need fileName?
	storageToConvert = myStorageDatabase.readFromDatabase();
	vector<vector<string>>::iterator myStorageIterator = storageToConvert.begin();
	//convert each string into task using storageConverter
	while(myStorageIterator!=storageToConvert.end()){
		myIndividualTask = myStorageConverter.convertStringToTask(*myStorageIterator);
		myConvertedTask.push_back(myIndividualTask);
		myStorageIterator++;
	}

	//pack tasks into state and return as state
	stateToLoad.setAllTask(myConvertedTask);

	return stateToLoad;
}

void StorageExecutor::saveToStorage(State stateToSave){

	StorageDatabase myStorageDatabase;
	StorageConverter myStorageConverter; 
	vector<vector<string>> convertedTaskStringStorage; 
	vector<string> individualConvertedTask;

	vector<Task> taskToStore = stateToSave.getAllTask(); 
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