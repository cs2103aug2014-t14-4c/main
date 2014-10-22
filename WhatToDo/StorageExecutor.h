#pragma once

#include "State.h"
#include "StorageConverter.h"
#include "StorageDatabase.h"
#include <string>
#include <vector>


using namespace std;

class StorageExecutor{
	private: 
		vector<string> myStorage;
		vector<vector<string>> storageToConvert; 
		StorageDatabase myStorageDatabase;
		StorageConverter myStorageConverter; 
		State stateToLoad; 
		Task myIndividualTask; 
		vector<vector<string>> convertedTaskStringStorage; 
		vector<string> individualConvertedTask;
		vector<Task> myConvertedTask;
		vector<Task> taskToStore;
	
public:
		StorageExecutor(void);
		
		//primary functions
		State loadFromStorage();
		void saveToStorage(State stateToSave);
		
		//supporting functions
		void processVectorToTaskConversion(vector<vector<string>>::iterator vectorStringIterator);
		State processTaskAddition(vector<Task>::iterator taskIterator);
		void StorageExecutor::convertAllTaskToString(vector<Task>::iterator taskIterator);

};


