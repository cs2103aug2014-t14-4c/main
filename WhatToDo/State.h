#pragma once
#include <string>
#include <vector>
#include "Task.h"
using namespace std;

class State {
	public:
		State(void);
		void addTask(Task taskToAdd);
		void deleteTask(int taskIndexToDelete);
		void doneTask(int taskIndexToDo);
		void clearAllTasks();
		vector<Task> getAllTasks();
		vector<Task> getTimedTasks();
		vector<Task> getDeadlineTasks();
		vector<Task> getFloatingTasks();
		void setAllTasks(vector<Task> tasksToAdd);
		void setUserMessage(string stringToSet);
		string getUserMessage();

	private:
		vector<Task> entireListOfTasks;
		string userMessage;

};

