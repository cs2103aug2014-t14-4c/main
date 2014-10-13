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
		vector<Task> myConvertedTask; 
		StorageDatabase myStorageDatabase;
		StorageConverter myStorageConverter; 
		State stateToLoad; 
		Task myIndividualTask; 
		vector<vector<string>> convertedTaskStringStorage; 
		vector<string> individualConvertedTask;
	public:
		StorageExecutor(void);
		State loadFromStorage();
		void saveToStorage(State stateToSave);

		//HELLLLO haha hahaha storageExecutor
};


