//@author A0116278B
//****************************************************************************
//StorageConverter is the class that is responsible for all the aspects of 
//the conversions when an user wants to save a State to database or load a 
//State from database. The two main conversions involved are...

//1)converting from a Task to string
//2)converting from a string to Task

//for each type of conversion, the process is further breaked down into smaller 
//pieces or called subfunctions to apply the Single Level of Abstraction 
//Principle. After conversion is complete, the relevant info are returned to 
//the other StorageExecutor to either be written to database, or return a State
//If an error occurred at any of the conversion operations, an error message
//will be logged. 

//sample usage:
//string taskString =storageConverterObj.convertTaskToString(Task taskToConvert);
//Task myTask = storageConverterObj.convertStringToTask(vector<string> 
//stringToConvert);
//****************************************************************************
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "Task.h"
#include <exception>
#include <fstream>

using namespace std;
const int MAX_SIZE = 255;
<<<<<<< HEAD
const string LOG_FILE_NAME = "storageLogs.txt";
=======
const string LOG_FILE_NAME = "storageLog.txt";
>>>>>>> 9a5aef7f09c1fcf33aec1a1885f8d02bcabd82db
const string STRING_TRUE = "1";
const string STRING_FALSE = "0";
const bool LOGGING_MODE_ON = true;

//functions that thrown the messages
const string STORAGE_LOGGING_TEMPLATE = "Function called: %s\nError Message: %s";
const string STORAGE_FUNCTION_CONVERT_PTIME_START = "convertStringStartTimeToTask();";
const string STORAGE_FUNCTION_CONVERT_PTIME_END = "convertStringEndTimeToTask();";
const string STORAGE_FUNCTION_CONVERT_PTIME_DEADLINE = "convertStringDeadLineToTask();";
const string STORAGE_FUNCTION_CONVERT_ISDONE = "ConvertStringIsDoneToTask(Task &convertedTask);";

//error messages
const string STORAGE_MSG_PTIME_START_ERROR = "Start Datetime false format.\n";
const string STORAGE_MSG_PTIME_END_ERROR = "End Datetime false format.\n";
const string STORAGE_MSG_PTIME_DEADLINE_ERROR = "Deadline false format.\n";
const string STORAGE_MSG_ISDONE_ERROR = "Task IsDone false format. \n";

//for documentation and readability
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

