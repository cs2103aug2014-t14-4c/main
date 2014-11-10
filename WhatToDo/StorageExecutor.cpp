//@author A0116278B
#include "StorageExecutor.h"

using namespace std; 

StorageExecutor::StorageExecutor(void){
	_logFileName == LOG_FILE_NAME; 
}

//loadFromStorage reads file, converts string into task
//packs tasks into a State and return as a state
State StorageExecutor::loadFromStorage(){

	readFileAndConvertString();
	vector<Task>::iterator taskIterator = _convertedTaskVector.begin();
	_stateToLoad = processTaskAddition(taskIterator);
	
	return _stateToLoad;
}

//saveToStorage first gets all tasks from state
//convert tasks to vector<string>
//write the string to database 
void StorageExecutor::saveToStorage(State stateToSave){
	
	//ensures that State does not return a NULL pointer
	assert(&stateToSave!=NULL);
	_taskToStore = stateToSave.getAllTasks(); 

	vector<Task>::iterator myTaskIterator = _taskToStore.begin();
	convertAllTaskToString(myTaskIterator);
	_storageDatabaseObj.writeToDatabase(_convertedStringStorage);
	
	return;
}

//adds converted Tasks into a State 
//returns the State after all Tasks are added
State StorageExecutor::processTaskAddition(vector<Task>::iterator taskIterator){

	while(taskIterator!= _convertedTaskVector.end()){
		_stateToLoad.addTask(*taskIterator); 
		taskIterator++; 
	}
	return _stateToLoad;
}

//read from database
//convert each string into task using storageConverter
//if any exceptions were caught during the conversion process
//errors could be from any of the sub-conversion functions
//conversions have failed and State will be loaded from backup 
//file
void StorageExecutor::readFileAndConvertString(){
	try{
		_storageToConvert = _storageDatabaseObj.readFromDatabase();
		vector<vector<string>>::iterator myStorageIterator = _storageToConvert.begin();
		processVectorStringToTaskConversion(myStorageIterator);
	} catch(exception&){
		compileErrorMessage(STORAGE_FUNCTION_LOAD_FROM_STORAGE,STORAGE_MSG_DATABASE_ERROR);
		logErrorMessage(_logErrorMessage);
		_storageToConvert.clear();

		logErrorMessage(STORAGE_MSG_LOAD_FROM_BACKUP); 
		_storageToConvert = _storageDatabaseObj.readFromBackUpDatabase();
		vector<vector<string>>::iterator myStorageIterator = _storageToConvert.begin();
		processVectorStringToTaskConversion(myStorageIterator);
	}
}

//conversion from vector<string> to Task
//exception handling when conversion isn't successful
void StorageExecutor::processVectorStringToTaskConversion(vector<vector<string>>::
	iterator vIterator){
	//convert string to task
	try{
		while(vIterator!=_storageToConvert.end()){
			_individualTask = _storageConverterObj.convertStringToTask(*vIterator);
			_convertedTaskVector.push_back(_individualTask);
			vIterator++;
		}
		return;
	} catch(exception&){
		compileErrorMessage(STORAGE_FUNCTION_VECTOR_STRING_TO_TASK_CONVERSION, 
							STORAGE_MSG_CONVERSION_ERROR);
		logErrorMessage(_logErrorMessage); 
		throw;
	}
}

//converts Tasks to strings
//store the converted string into a vector of strings
void StorageExecutor::convertAllTaskToString(vector<Task>::iterator taskIterator){

	_convertedStringStorage.clear();
	while(taskIterator!=_taskToStore.end()){
		_individualConvertedTask = _storageConverterObj.
			convertTaskToString(*taskIterator);	
		_convertedStringStorage.push_back(_individualConvertedTask);
		taskIterator++;
	}
	return;
}

//error messages will be compiled to a standard template before 
//it is to be written to file
void StorageExecutor::compileErrorMessage(string errorMessageLocation, 
										  string errorMessage){
	
	sprintf_s(_logErrorMessage, STORAGE_LOGGING_TEMPLATE.c_str(), 
			  errorMessageLocation.c_str(), errorMessage.c_str());

	return;
}

//logging function to write error message to file
void StorageExecutor::logErrorMessage(string errorMessage){
	if(LOGGING_MODE_ON == true){
		ofstream writeToLogFile;
		string currentTime = to_simple_string(second_clock::local_time());
		writeToLogFile.open(LOG_FILE_NAME, ios::app);
		writeToLogFile << currentTime << endl << errorMessage << endl;
		writeToLogFile.close();
	} 

	return;
}

