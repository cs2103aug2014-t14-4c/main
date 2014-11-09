//@author A0116278B
//****************************************************************************
//StorageExecutor is the class that depends on both StorageConverter as well 
//as StorageDatabase in order to execute its functions. 
//StorageExecutor acts as the Central Nerves System for the storage component
//what it does is handling and managing the different Tasks. Its two main 
//functions are 

//1) Saving a current State to storage
//2) Loading a saved .txt file and return a State

//Errors will also be logged if any of the component is not working as supposed

//sample usage:
//State stateToLoad = storageExecutorObj.loadFromStorage();
//storageExecutorObj.saveToStorage(); 
//****************************************************************************

#pragma once

#include "State.h"
#include "StorageConverter.h"
#include "StorageDatabase.h"
#include <string>
#include <vector>

using namespace std;

//error messages and error locations
const string FUNCTION_VECTOR_STRING_TO_TASK_CONVERSION = 
	"processVectorStringToTaskConversion(vector<vector<string>>::"
	"iterator vIterator)";
const string STORAGE_FUNCTION_LOAD_FROM_STORAGE = 
	"loadFromStorage();";
const string STORATE_FUNCTION_LOAD_FROM_BACKUP = 
	"raedFromBackUpDatabase();";

const string STORAGE_MSG_CONVERSION_ERROR = 
	"Conversion was unsuccessful!\n";
const string STORAGE_MSG_DATABASE_ERROR = 
	"Database file corrupted, reading from backup!\n";
const string STORAGE_MSG_BACKUP_ERROR = 
	"Backup file corrupted, creating a new copy!\n";
const string STORAGE_MSG_LOAD_FROM_BACKUP = 
	"Loading from Backup database...";


class StorageExecutor{
	private:
		string _logFileName; 
		char _logErrorMessage[MAX_SIZE]; 

		//obj requirements.
		StorageDatabase _storageDatabaseObj;
		StorageConverter _storageConverterObj; 

		State _stateToLoad; 
		Task _individualTask; 

		vector<vector<string>> _storageToConvert; 
		vector<vector<string>> _convertedStringStorage; 
		vector<string> _individualConvertedTask;
		vector<Task> _convertedTaskVector;
		vector<Task> _taskToStore;
	public:
		StorageExecutor(void);
		
		//primary functions
		State loadFromStorage();
		void saveToStorage(State stateToSave);
		
		//supporting functions
		State processTaskAddition(vector<Task>::iterator taskIterator);
		void readFileAndConvertString();
		void processVectorStringToTaskConversion(vector<vector<string>>::
												 iterator vectorStringIterator);
		void convertAllTaskToString(vector<Task>::iterator taskIterator);
		void logErrorMessage(string errorMessage);
		void compileErrorMessage(string errorMessageLocation, 
								 string errorMessage);
};


