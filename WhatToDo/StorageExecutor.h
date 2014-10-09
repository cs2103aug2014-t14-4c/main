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
	public:
		StorageExecutor(void);
		State loadFromStorage();
		void saveToStorage(State stateToSave);

		//HELLLLO haha hahaha storageExecutor
};


