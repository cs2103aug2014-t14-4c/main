#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "Task.h"

using namespace std;

class StorageConverter{
	private:
		Task convertedTask; 
		vector<string> taskStringAttributes;
		string taskDatetimeString; 
		string taskName;
		string taskTags;
		string taskIsDone; 

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

		//subfunctions for conversion from task to string
		string convertTaskPtimeToString(ptime myDatetime);
		string convertTaskPtimeDurationToString(time_duration myDuration);
		string convertTaskBoolToString(bool boolToConvert);
		string convertTaskTagVectorToString(vector<string> taskTags);

		//primary conversion function
		Task convertStringToTask(vector<string> stringToConvert);
		
		//secondary functions for conversion from string to task
		vector<string> taskTagStringToVectorConverter(string tagString);
		void convertStringIsdoneToTask();
		void convertStringStartDatetimeToTask();
		void convertStringEndDatetimeToTask();
		void convertStringDeadlineToTask();
		void convertStringTasktagToTask();
}; 

