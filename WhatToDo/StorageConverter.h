//@author A0116278B

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "Task.h"
#include <exception>

using namespace std;

class StorageConverter{
	private:
		//attributes for StorageConverter
		vector<string> _taskStringAttributes;
		string _taskDatetimeString; 
		string _taskName;
		string _taskTags;
		string _taskIsDone; 

	public:
		static string TITLE_TASKSTARTDATETIME;
		static string TITLE_TASKENDDATETIME;
		static string TITLE_TASKDEADLINE;
		static string TITLE_TASKNAME;
		static string TITLE_TASKTAGS;
		static string TITLE_TASKISDONE;
		static string NOT_A_DATETIME;
		
		StorageConverter(void);

		//primary conversion functions
		vector<string> convertTaskToString(Task taskToConvert);
		Task convertStringToTask(vector<string> stringToConvert);

		//subfunctions for conversion from task to string
		string convertTaskPtimeToString(ptime myDatetime);
		string convertTaskPtimeDurationToString(time_duration myDuration);
		string convertTaskBoolToString(bool boolToConvert);
		string convertTaskTagVectorToString(vector<string> taskTags);
		string convertTaskNameToString(Task taskToConvert);
		
		//subfunctions for conversion from string to task
		void convertStringIsdoneToTask(Task& convertedTask);
		void convertStringStartDatetimeToTask(Task& convertedTask);
		void convertStringEndDatetimeToTask(Task& convertedTask);
		void convertStringDeadlineToTask(Task& convertedTask);
		void convertStringTasktagToTask(Task& convertedTask);
		vector<string> convertTaskTagStringToVector(string tagString);
}; 

