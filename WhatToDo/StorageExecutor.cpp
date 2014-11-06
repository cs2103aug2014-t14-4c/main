#include "StorageExecutor.h"

using namespace std; 

StorageExecutor::StorageExecutor(void){
}

State StorageExecutor::loadFromStorage(){
	
	readFileAndConvertString();
	//pack tasks into state and return as state
	vector<Task>::iterator taskIterator = _convertedTaskVector.begin();
	assert(&taskIterator!=NULL);
	_stateToLoad = processTaskAddition(taskIterator);

	return _stateToLoad;
}

void StorageExecutor::saveToStorage(State stateToSave){
	//first get all task for a given State and returns a vector of Tasks
	assert(&stateToSave!=NULL);
	
	_taskToStore = stateToSave.getAllTasks(); 

	//for each task, convert to string using string converter
	vector<Task>::iterator myTaskIterator = _taskToStore.begin();
	convertAllTaskToString(myTaskIterator);
	//send to StorageDatabase for writing of file
	_storageDatabaseObj.writeToDatabase(_convertedStringStorage);
	
	return;
}

void StorageExecutor::processVectorStringToTaskConversion(vector<vector<string>>::iterator vIterator){
	//convert string to task
	try{
		while(vIterator!=_storageToConvert.end()){
			_individualTask = _storageConverterObj.convertStringToTask(*vIterator);
			_convertedTaskVector.push_back(_individualTask);
			vIterator++;
		}
		return;
	} catch(exception&){
		//catch errors from conversion
		throw;
	}
}

State StorageExecutor::processTaskAddition(vector<Task>::iterator taskIterator){

	//adding task for loading by state
	while(taskIterator!= _convertedTaskVector.end()){
		_stateToLoad.addTask(*taskIterator); 
		taskIterator++; 
	}
	return _stateToLoad;
}

void StorageExecutor::convertAllTaskToString(vector<Task>::iterator taskIterator){

	_convertedStringStorage.clear();
	while(taskIterator!=_taskToStore.end()){
		_individualConvertedTask = _storageConverterObj.convertTaskToString(*taskIterator);
		//store the converted string into a vector of strings
		_convertedStringStorage.push_back(_individualConvertedTask);
		taskIterator++;
	}

	return;
}

void StorageExecutor::readFileAndConvertString(){

	//convert each string into task using storageConverterdddd
	try{
		_storageToConvert = _storageDatabaseObj.readFromDatabase();
		assert(&_storageToConvert != NULL);
		//cannot read a null pointer
		vector<vector<string>>::iterator myStorageIterator = _storageToConvert.begin();
		processVectorStringToTaskConversion(myStorageIterator);
	} catch(exception&){
		//load from backupfile
		//log message " loading from backup";
		_storageToConvert.clear();
		_storageToConvert = _storageDatabaseObj.readFromBackUpDatabase();
		vector<vector<string>>::iterator myStorageIterator = _storageToConvert.begin();
		processVectorStringToTaskConversion(myStorageIterator);
	}
}