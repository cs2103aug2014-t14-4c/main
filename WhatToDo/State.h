#ifndef STATE_H
#define STATE_H

#include "Task.h"
using namespace std;

class State{
	private:
		vector<Task> _entireListOfTasks;
		string _userMessage;
		int maxIndex;
	public:
		//Constructor
		State();

		//Operations
		void addTask(Task taskToAdd);
		void deleteTask(int taskIndexToDelete);
		void clearAllTasks();
		vector<Task> getAllTasks();
		vector<Task> getTimedTasks();
		vector<Task> getDeadlineTasks();
		vector<Task> getFloatingTasks();
		void setAllTasks(vector<Task> tasksToSet);
		void setUserMessage(string stringToSet);
		string getUserMessage();
};


#endif