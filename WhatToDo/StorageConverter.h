#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Task.h"

using namespace std;

class StorageConverter{
	private:


	public:
		static string _getTaskType;
		static string _getTaskStartDatetime;
		static string _getTaskEndDatetime;
		static string _getTaskDeadline;
		static string _getTaskDuration;
		static string _getTaskName;
		static string _getTaskDetails;
		static string _getTaskTags;
		static string _getTaskIndex;
		static string _getTaskIsDone;

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

