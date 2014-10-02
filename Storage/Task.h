#pragma once
#include <string>
#include <vector>
#include <boost\date_time\posix_time\posix_time.hpp>
using namespace std; 

class Task
{
public:
	Task(void);
	int getTaskType();
	int getTaskDuration();
	string getTaskName();
	string getTaskDetails();
	vector<string> getTaskTags();
	int getTaskIndex();
	bool getIsDone();
};

