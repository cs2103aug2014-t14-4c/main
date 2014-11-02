#ifndef STATE_H
#define STATE_H
//
//1) Introduce Exceptions
//	a) if taskIndexToDelete is out of bounds --> Error
//
#include "Task.h"
using namespace std;

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

		//Operations
		void addTask(Task taskToAdd, bool isUserCommand = false, int specifiedIndex = -1);
		void deleteTask(int taskIndexToDelete, bool isUserCommand = false);
		void doneTask(int taskIndexToDo, bool isUserCommand = false);
		void clearAllTasks();
		vector<Task> getAllTasks();
		vector<Task> getTimedTasks();
		vector<Task> getDeadlineTasks();
		vector<Task> getFloatingTasks();
		int getLastActionType();
		int getLastActionTaskIndex();
		void setAllTasks(vector<Task> tasksToSet);
		void setUserMessage(string stringToSet);
		void setActionMessage(string stringToSet);
		void setLastActionType(int actionTypeToSet);
		void setLastActionTaskIndex(int actionTaskIndexToSet);
		string getUserMessage();
		string getActionMessage();
		

		enum actionType { NONE = 1, CHANGED, DELETED };
};

#endif