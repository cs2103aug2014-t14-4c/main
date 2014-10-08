#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Task.h"

using namespace std;

class StorageConverter{
	private:
		string _getTaskType;
		string _getTaskStartDateime;
		string _getTaskEndDatetime;
		string _getTaskDeadline;
		string _getTaskDuration;
		string _getTaskName;
		string _getTaskDetails;
		string _getTaskTags;
		string _getTaskIndex;
		string _getTaskIsDone;

	public:
		string ptimeToStringConverter(ptime myDatetime);
		string ptimeDurationToStringConverter(time_duration myDuration);
		StorageConverter(void);
		vector<string> convertTaskToString(Task taskToConvert);
		Task convertStringToTask(vector<string> stringToConvert);
		string boolConverter(bool boolToConvert);
		string taskTagVectorToStringConverter(vector<string> taskTags);
		vector<string> taskTagStringToVectorConverter(string tagString);
		bool taskStringToBooleanConverter(string boolString);
};

