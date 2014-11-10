//@author A0110873L
//****************************************************************************
//Task is the most fundamental component within WhatToDo and is responsible 
//for storing important details of a task such as its start time, end time, 
//deadline, name, tags and status (done or not done). In additional, a Task 
//has two additional functions – firstly it is able to check if two Tasks 
//overlap, and secondly it is able to check if a Task begins earlier than 
//another Task. A Task also can be defined in many types:
//	1)Floating Tasks - no start date time, no end date time and no deadline
//  2)Deadline Tasks
//		a) All Day - Meaning that the entire day is demarketed as the deadline
//		b) Time - Meaning that the deadline has a specific time
//	3)Fixed Tasks
//		a) Day
//			i) All Day - Meaning that one entire day is demarketed for the Task
//		   ii) Day To Time - Meaning that the start date is specified wih no 
//				time and the end date time is specified
//		  iii) Day To Day - Meaning that the start and end dates are both 
//				specified with no times specified	
//		b) Start - Meaning that the start time is specified without any end
//			datetime
//		c) Time 
//			i) Time Within Day - Meaning that the start time and end time are
//				specified within a single day
//		   ii) Time Across Day - Meaning that the start time and end time are
//				specified over one day
//		  iii) Time To Day - Meaning that the start time is specified and the
//				end date is specified with no time
//
//*Note: datetimes which occupy an entire day are marked with 1 second 
//		(000001 in HHMMSS)
//
//Logging is used to tracked changes within the internal workings of a Task
//However, it can be toggled on and off by the developer on an optional basis.
//This is because logging for a large number of Tasks may slow down the 
//computational processes within WhatToDo. This can be easily changed by
//setting _loggingModeOn to either true or false in the constructor.
//****************************************************************************

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

//Constants
const int NUM_OF_COMP_FUNCTIONS = 8;
const int MARKED_AS_FULL_DAY = 1;
const int EMPTY = 0;
const string ERR_MSG_INVALID_FUNCTION_CALL = "ERROR: Function called does not exist\n";
const string ERR_MSG_INVALID_TASK_TYPE = "ERROR: Task Type does not exist\n";
const string LOG_TASK_FILE_NAME = "Task.txt";
const string LOG_MSG_INITIATE = "Constructor called: Task()\n";
const string LOG_MSG_COMPARE = "Function called: compare()\n";
const string LOG_MSG_TASK_SORTED_BEFORE = "Function called: isTaskSortedBefore()\n";
const string LOG_MSG_TASK_OVERLAP = "Function called: isTaskOverlapWith()\n";
const string LOG_MSG_TASK_DONE = "Function called: setTaskIsDone()\n";

class Task {
	private:
		//Attributes for Task
		ptime _taskStartDateTime;
		ptime _taskEndDateTime;
		ptime _taskDeadline;
		string _taskName;
		vector<string> _taskTags;
		int _taskIndex;
		bool _isDone;

		//Attributes for Logging
		string _logFileName;
		bool _loggingModeOn;
		char buffer[255];

	public:
		//Constructor
		Task();

		//Setters
		void setTaskStartTime(ptime dateTimeToSet);
		void setTaskEndTime(ptime dateTimeToSet);
		void setTaskDeadline(ptime dateTimeToSet);
		void setTaskName(string nameToSet);
		void setTaskTags(vector<string> tagsToSet);
		void setTaskIndex(int indexToSet);
		void setTaskIsDone(bool doneStatusToSet = true);
		void setTaskIsNotDone();

		//Getters
		int getTaskType();
		int getTaskIndex();
		ptime getTaskStartTime();
		ptime getTaskEndTime();
		ptime getTaskDeadline();
		time_duration getTaskDuration();
		string getTaskName();
		vector<string> getTaskTags();
		bool getTaskIsDone();
		
		//Primary Operations
		bool hasStartDateTime();
		bool hasEndDateTime();
		bool hasDeadline();
		bool isFullDay(ptime dateTimeToCheck);
		bool isStartDateEqualEndDate();
		bool isTaskTypeFixedDay(Task myTask);
		bool isTaskTypeFixedTime(Task myTask);
		bool isTaskOverlapWith(Task myTask);
		bool isEarlierThan(Task myTask);
		bool isTaskSortedBefore(Task firstTask, Task secondTask);
		bool compare(Task firstTask, Task secondTask, bool *orderConfirmed, int functionToCall);

		//Secondary Operations
		bool compareByFloat(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByDate(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByDeadlineAllDay(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByDeadlineTime(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedDay(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedStart(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedTime(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedTimeAndStart(Task firstTask, Task secondTask, bool *orderConfirmed);
		
		//Logging
		void log(string stringToLog);
		bool isLoggingModeOn();
		void setLoggingModeOff();
		void setLoggingModeOn();

		//Enumeration
		enum TaskType {
			 FLOATING = 1, DEADLINE_TIME, DEADLINE_ALLDAY, FIXED_ALLDAY, FIXED_DAY_TO_DAY, 
			 FIXED_DAY_TO_TIME, FIXED_START, FIXED_TIME_WITHIN_DAY, FIXED_TIME_ACROSS_DAY, 
			 FIXED_TIME_TO_DAY, NOT_A_TASK_TYPE 
		};

		//Compare Functions are arranged in order of precedence from greatest priority starting from 1.
		enum CompareType {
			COMPARE_FLOAT = 1, COMPARE_DATE, COMPARE_DEADLINE_ALLDAY, COMPARE_DEADLINE_TIME,
			COMPARE_FIXED_DAY, COMPARE_FIXED_START, COMPARE_FIXED_TIME, COMPARE_FIXED_TIME_START
		};
};

#endif