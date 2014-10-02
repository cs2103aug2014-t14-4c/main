#pragma once

#include "Task.h"
#include <vector>
using namespace std;
class State
{
public:
	State(void);
	void setAllTask(vector<Task> taskToSet);
	vector<Task> getAllTask();
};

