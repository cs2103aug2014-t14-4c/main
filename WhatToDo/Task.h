//****************************************************************************
//A Task is the most fundamental component 
//within WhatToDo and is responsible for storing 
//important details of a task such as its start time, 
//end time, deadline, name, tags and status (done 
//or not done). In additional, a Task has two 
//additional functions – firstly it is able to check if 
//two Tasks overlap, and secondly it is able to 
//check if a Task begins earlier than another Task.
//
//@author A0110873L
//****************************************************************************

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

const int NUM_OF_COMP_FUNCTIONS = 8;
const string MSG_ERR_INVALID_FUNCTION_CALL = "INVALID_ARGUMENT: Function called does not exist\n";

class Task{
	private:
		ptime _taskStartDateTime;
		ptime _taskEndDateTime;
		ptime _taskDeadline;
		string _taskName;
		string _taskDetails; //Not used for now
		vector<string> _taskTags;
		int _taskIndex;
		int _taskType;
		bool _isDone;

	public:
		//Constructor
		Task();

		//Setters
		void setTaskStartTime(ptime dateTimeToSet);
		void setTaskEndTime(ptime dateTimeToSet);
		void setTaskDeadline(ptime dateTimeToSet);
		void setTaskName(string nameToSet);
		void setTaskDetails(string detailsToSet); // Not used for now
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
		string getTaskDetails();//Not used for now
		vector<string> getTaskTags();
		bool getTaskIsDone();
		
		//Operations
		bool hasStartTime();
		bool hasEndTime();
		bool hasDeadline();
		bool isTaskOverlapWith(Task myTask);
		bool isEarlierThan(Task myTask);
		bool isTaskSortedBefore(Task firstTask, Task secondTask);
		bool compare(Task firstTask, Task secondTask, bool *orderConfirmed, int functionToCall);

		//Level 2 Operations
		bool compareByFloat(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByDateTime(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByDeadlineAllDay(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByDeadlineTime(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedAllDay(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedStart(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedTime(Task firstTask, Task secondTask, bool *orderConfirmed);
		bool compareByFixedTimeAndStart(Task firstTask, Task secondTask, bool *orderConfirmed);

		//Enumeration
		enum TaskType{
			 FLOATING = 1, DEADLINE_TIME, DEADLINE_ALLDAY, FIXED_TIME, FIXED_START, FIXED_ALLDAY
		};

		enum CompareType{
			COMPARE_FLOAT = 1, COMPARE_DATETIME, COMPARE_DEADLINEALLDAY, COMPARE_DEADLINETIME,
			COMPARE_FIXEDALLDAY, COMPARE_FIXEDSTART, COMPARE_FIXEDTIME, COMPARE_FIXEDTIMEANDSTART
		};

};

//FLOATING Tasks have no StartDateTime and no Deadline
//DEADLINE_ALLDAY Tasks have deadline time 000001 (HHMMSS)
//DEADLINE_TIME Tasks have deadline times that are not marked with time 000001
//FIXED_TIME Tasks have StartDateTimes and EndDateTimes which only use HHMM, SS are not touched
//FIXED_ALLDAY Tasks have StartDateTime, no EndDateTime, and it's StartDateTime is marked with time 000001
//FIXED_START Tasks have StartDateTime, no EndDateTime
//FIXED_


#endif