#include "StorageExecutor.h"

using namespace std; 

StorageExecutor::StorageExecutor(void){
	_logFileName == LOG_FILE_NAME; 
	_loggingModeOn = true; 
}

//loadFromStorage reads file, converts string into task
//packs tasks into a State and return as a state
State StorageExecutor::loadFromStorage(){

	readFileAndConvertString();
	vector<Task>::iterator taskIterator = _convertedTaskVector.begin();
	assert(&taskIterator!=NULL);
	_stateToLoad = processTaskAddition(taskIterator);
	
	return _stateToLoad;
}

//saveToStorage first gets all tasks from state
//convert tasks to vector<string>
//write to databas the string
void StorageExecutor::saveToStorage(State stateToSave){
	assert(&stateToSave!=NULL);
	_taskToStore = stateToSave.getAllTasks(); 

	vector<Task>::iterator myTaskIterator = _taskToStore.begin();
	convertAllTaskToString(myTaskIterator);
	_storageDatabaseObj.writeToDatabase(_convertedStringStorage);
	
	return;
}

//conversion from vector<string> to Task
//exception handling when conversion isn't successful
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
		compileErrorMessage(FUNCTION_VECTOR_STRING_TO_TASK_CONVERSION,MSG_CONVERSION_ERROR);
		logErrorMessage(_logErrorMessage); 
		throw;
	}
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

//converts Tasks to strings
//store the converted string into a vector of strings
void StorageExecutor::convertAllTaskToString(vector<Task>::iterator taskIterator){

	_convertedStringStorage.clear();
	while(taskIterator!=_taskToStore.end()){
		_individualConvertedTask = _storageConverterObj.convertTaskToString(*taskIterator);	
		_convertedStringStorage.push_back(_individualConvertedTask);
		taskIterator++;
	}
	return;
}

//read from database
//convert each string into task using storageConverter
//if any exceptions were caught during the conversion process
//errors could be from any of the sub-conversion functions
//conversions have failed and will be load from backup file
//if backup also fails, a new file will be created
void StorageExecutor::readFileAndConvertString(){
	try{
		_storageToConvert = _storageDatabaseObj.readFromDatabase();
		vector<vector<string>>::iterator myStorageIterator = _storageToConvert.begin();
		processVectorStringToTaskConversion(myStorageIterator);
	} catch(exception&){
		compileErrorMessage(FUNCTION_LOAD_FROM_STORAGE,MSG_DATABASE_ERROR);
		logErrorMessage(_logErrorMessage);
		_storageToConvert.clear();
		_storageToConvert = _storageDatabaseObj.readFromBackUpDatabase();
		vector<vector<string>>::iterator myStorageIterator = _storageToConvert.begin();
		processVectorStringToTaskConversion(myStorageIterator);
	}
}
	 
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

void StorageExecutor::compileErrorMessage(string errorMessageLocation, string errorMessage){
	
	sprintf_s(_logErrorMessage, LOGGING_TEMPLATE.c_str(), errorMessageLocation.c_str(), errorMessage.c_str());

	return;
}

State StorageExecutor::loadNewFile(){
	State newState;
	return newState;  
}