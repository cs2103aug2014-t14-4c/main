//@author A0116278B

#pragma once

#include "State.h"
#include "StorageConverter.h"
#include "StorageDatabase.h"
#include <string>
#include <vector>

using namespace std;

const string FUNCTION_VECTOR_STRING_TO_TASK_CONVERSION = 
	"processVectorStringToTaskConversion(vector<vector<string>>::"
	"iterator vIterator)";
const string FUNCTION_LOAD_FROM_STORAGE = "loadFromStorage();";
const string FUNCTION_LOAD_FROM_BACKUP = "raedFromBackUpDatabase();";

const string MSG_CONVERSION_ERROR = "Conversion was unsuccessful!\n";
const string MSG_DATABASE_ERROR = "Database file corrupted, reading from backup!\n";
const string MSG_BACKUP_ERROR = "Backup file corrupted, creating a new copy!\n";


class StorageExecutor{
	private:
		//logging variables
		string _logFileName; 
		bool _loggingModeOn;
		char _logErrorMessage[MAX_SIZE]; 

		//obj requirements
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
		State loadNewFile();
		void saveToStorage(State stateToSave);
		
		//supporting functions
		State processTaskAddition(vector<Task>::iterator taskIterator);
		void readFileAndConvertString();
		void processVectorStringToTaskConversion(vector<vector<string>>::iterator vectorStringIterator);
		void convertAllTaskToString(vector<Task>::iterator taskIterator);
		void logErrorMessage(string errorMessage);
		void compileErrorMessage(string errorMessageLocation, string errorMessage);
};


