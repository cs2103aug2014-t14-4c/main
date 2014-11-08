//@author A0116278B

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "Task.h"
#include <exception>
#include <fstream>

using namespace std;
const int MAX_SIZE = 255;
const string LOG_FILE_NAME = "filelogs.txt";
const string STRING_TRUE = "1";
const string STRING_FALSE = "0";
const bool LOGGING_MODE_ON = true;

const string LOGGING_TEMPLATE = "Function called: %s\nError Message: %s";

const string FUNCTION_CONVERT_PTIME_START = "convertStringStartTimeToTask();";
const string FUNCTION_CONVERT_PTIME_END = "convertStringEndTimeToTask();";
const string FUNCTION_CONVERT_PTIME_DEADLINE = "convertStringDeadLineToTask();";
const string FUNCTION_CONVERT_ISDONE = "ConvertStringIsDoneToTask(Task &convertedTask);";

const string MSG_PTIME_START_ERROR = "Start Datetime false format.\n";
const string MSG_PTIME_END_ERROR = "End Datetime false format.\n";
const string MSG_PTIME_DEADLINE_ERROR = "Deadline false format.\n";
const string MSG_ISDONE_ERROR = "Task IsDone false format. \n";
//

const string TITLE_TASKSTARTDATETIME = "Start Datetime: ";
const string TITLE_TASKENDDATETIME = "End Datetime: ";
const string TITLE_TASKDEADLINE = "Task Deadline: ";
const string TITLE_TASKNAME = "Task Name: ";
const string TITLE_TASKTAGS = "Task Tags: ";
const string TITLE_TASKISDONE = "Task isDone Status: ";
const string NOT_A_DATETIME = "not-a-date-time"; 

class StorageConverter{
	private:
		//attributes for StorageConverter
		vector<string> _taskStringAttributes;
		string _taskDatetimeString; 
		string _taskName;
		string _taskTags;
		string _taskIsDone; 
		string _logFileName;
		char _logErrorMessage[MAX_SIZE]; 


	public:

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

		//logging function
		void logErrorMessage(string logString);
		void compileErrorMessage(string errorMessageLocation, 
								 string errorMessage);
}; 

