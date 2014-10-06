#pragma once
#include "State.h"
using namespace std;

class StorageExecutor {
	public:
		StorageExecutor(void);
		State loadFromStorage();
		void saveToStorage(State stateToSave);

	private:
	
};

