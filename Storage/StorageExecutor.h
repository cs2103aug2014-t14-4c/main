#include "State.h"
#include "StorageConverter.h"
#include "StorageDatabase.h"
#include <string>
#include <vector>

#pragma once
using namespace std;

class StorageExecutor{
	private: 
		vector<string> myStorage;
	public:
		StorageExecutor(void);
		State loadFromStorage();
		void saveToStorage(State stateToSave);
};

