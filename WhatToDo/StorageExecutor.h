//@author A0116278B

#pragma once

#include "State.h"
#include "StorageConverter.h"
#include "StorageDatabase.h"
#include <string>
#include <vector>


using namespace std;

class StorageExecutor{
private: 
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
		void processVectorStringToTaskConversion(vector<vector<string>>::iterator vectorStringIterator);
		State processTaskAddition(vector<Task>::iterator taskIterator);
		void convertAllTaskToString(vector<Task>::iterator taskIterator);
		void readFileAndConvertString();

};


