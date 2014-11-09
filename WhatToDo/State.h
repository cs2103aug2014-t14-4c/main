//****************************************************************************
//@author A0110873L
//
//State is responsible for storing a list of Tasks. State primarily deals with
//the adding, deleting of Tasks. Also, when a Task is completed,
//State is able to set the Task as done. Other than this, State can return
//the caller a sorted list of specified Tasks based on these specifications:
//	1) Timed - Contain information such as StartDate or EndDate, but does not
//     have a deadline
//	2) Deadline - Specifically has a deadline
//	3) Floating - No StartDate and deadline
//
//Upon the execution of any function, State keeps track of its latest action
//type:
//	1) NONE - meaning that no changes were made
//  2) CHANGED - meaning that the State has changed with the addition of a new
//			task or a task is marked as done
//	3) DELETED - meaning that a Task has been deleted from State
//
//This information can be extracted from caller components such as LogicData
//through its getter functions
//****************************************************************************

#ifndef STATE_H
#define STATE_H

#include "Task.h"
#include <fstream>
using namespace std;

//Constants
const int UNSPECIFIED_INDEX = -1;
const int INITIAL_INDEX = 0;
const int TO_THE_RIGHT_BY_ONE = 1;
const bool UNSPECIFIED_USER_COMMAND = false;

const string LOG_STATE_FILE_NAME = "StateLog.txt";
const string LOG_MSG_TASK_ADDED = "Function called: addTask()\n";
const string LOG_MSG_TASK_DELETED = "Function called: deleteTask()\n";
const string LOG_MSG_TASK_DONE = "Function called: doneTask()\n";
const string LOG_MSG_TASKS_CLEARED = "Function called: clearAllTasks()\n";
const string LOG_MSG_TASKS_SORTED = "Function called: sortAllTasks()\n";

class State {
	private:
		//Attributes for State
		vector<Task> _entireListOfTasks;
		string _userMessage;
		string _actionMessage;
		int maxIndex;
		int _lastActionType;
		int _lastActionTaskIndex;

		//Attributes for Logging
		string _logFileName;
		bool _loggingModeOn;
		char buffer[255];

	public:
		//Constructor
		State();

		//Setters
		void setAllTasks(vector<Task> tasksToSet);
		void setUserMessage(string stringToSet);
		void setActionMessage(string stringToSet);
		void setLastActionType(int actionTypeToSet);
		void setLastActionTaskIndex(int actionTaskIndexToSet);
		
		//Getters
		string getUserMessage();
		string getActionMessage();
		int getLastActionType();
		int getLastActionTaskIndex();

		//Operations
		void addTask(Task taskToAdd, bool isUserCommand = UNSPECIFIED_USER_COMMAND, 
			int specifiedIndex = UNSPECIFIED_INDEX);
		void deleteTask(int taskIndexToDelete, 
			bool isUserCommand = UNSPECIFIED_USER_COMMAND);
		void doneTask(int taskIndexToDo, 
			bool isUserCommand = UNSPECIFIED_USER_COMMAND);
		void clearAllTasks();
		void sortAllTasks();
		vector<Task> getAllTasks();
		vector<Task> getTimedTasks();
		vector<Task> getDeadlineTasks();
		vector<Task> getFloatingTasks();
		bool isTimedTask(Task taskToCheck);
		bool isDeadlineTask(Task taskToCheck);
		bool isFloatingTask(Task taskToCheck);

		//Logging
		void log(string stringToLog);
		bool isLoggingModeOn();
		void setLoggingModeOff();
		void setLoggingModeOn();

		//Enumeration
		enum actionType { NONE = 1, CHANGED, DELETED };
};

#endif