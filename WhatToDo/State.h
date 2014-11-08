//****************************************************************************
//@author A0110873L
//State is responsible for storing a list of Tasks. State primarily deals with
//the adding, deleting of Tasks to itself. Also, when a Task is completed,
//State is able to set the Task as done. Other than this, State can return
//the caller a list of specified Tasks based on these specifications:
//	1) Timed - Contain information such as StartDate or EndDate, but does not
//     have a deadline
//	2) Deadline - Specifically has a deadline
//	3) Floating - No StartDate and deadline
//
//****************************************************************************

#ifndef STATE_H
#define STATE_H

#include "Task.h"
using namespace std;

const int UNSPECIFIED_INDEX = -1;
const bool UNSPECIFIED_USER_COMMAND = false;

class State{
	private:
		vector<Task> _entireListOfTasks;
		string _userMessage;
		string _actionMessage;
		int maxIndex;
		int _lastActionType;
		int _lastActionTaskIndex;

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
		void deleteTask(int taskIndexToDelete, bool isUserCommand = UNSPECIFIED_USER_COMMAND);
		void doneTask(int taskIndexToDo, bool isUserCommand = UNSPECIFIED_USER_COMMAND);
		void clearAllTasks();
		void sortAllTasks();
		vector<Task> getAllTasks();
		vector<Task> getTimedTasks();
		vector<Task> getDeadlineTasks();
		vector<Task> getFloatingTasks();

		//Enumeration
		enum actionType { NONE = 1, CHANGED, DELETED };
};

#endif