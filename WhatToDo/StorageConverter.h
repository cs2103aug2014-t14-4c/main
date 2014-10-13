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

	public:
		static string TITLE_TASKTYPE;
		static string TITLE_TASKSTARTDATETIME;
		static string TITLE_TASKENDDATETIME;
		static string TITLE_TASKDEADLINE;
		static string TITLE_TASKDURATION;
		static string TITLE_TASKNAME;
		static string TITLE_TASKDETAILS;
		static string TITLE_TASKTAGS;
		static string TITLE_TASKINDEX;
		static string TITLE_TASKISDONE;
		static string NOT_A_DATETIME;
		
		StorageConverter(void);

		//primary conversion functions
		vector<string> convertTaskToString(Task taskToConvert);
		Task convertStringToTask(vector<string> stringToConvert);

		//secondary coversion functions
		string ptimeToStringConverter(ptime myDatetime);
		string ptimeDurationToStringConverter(time_duration myDuration);
		string boolConverter(bool boolToConvert);
		string taskTagVectorToStringConverter(vector<string> taskTags);
		vector<string> taskTagStringToVectorConverter(string tagString);
		bool taskStringToBooleanConverter(string boolString);
};

