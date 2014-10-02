#pragma once
#include <string>
#include "Task.h"
using namespace std;

class StorageConverter {
	public:
		StorageConverter(void);
		string convertTaskToString(Task taskToConvert);
		Task convertStringToTask(string stringToConvert);

	private:

};

