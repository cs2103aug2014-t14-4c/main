#pragma once
#include <string>
#include <vector>
#include "Task.h"
#include "State.h"
using namespace std;

class Command {
	public:
		Command(void);
		virtual void execute();
		string getSearchKeyword();
		Task getCurrentTask();
		int getTaskIndex();
		bool getParsedStatus();
		void setSearchKeyword(string searchKeywordToSet);
		void setCurrentTask(Task currentTaskToSet);
		void setTaskIndex(int taskIndexToSet);
		void setParsedStatus(bool parsedStatus);

	protected:
		string _searchKeyword;
		Task _currentTask;
		int _taskIndex;
		string _userMessage;
		State _currentState;
		bool _isCommandValid;
};

