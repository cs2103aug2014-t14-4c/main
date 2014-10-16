#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include "Task.h"
#include "State.h"
#include "LogicData.h"
using namespace std;


class Command {
	public:
		Command(void);
		virtual void execute();

		// All Getter Functions
		int getTaskIndex();
		bool getParsedStatus();
		string getSearchKeyword();
		Task getCurrentTask();
		
		// All Setter Functions
		void setTaskIndex(int commandTaskIndexToSet);
		void setParsedStatus(bool parsedStatus);
		void setSearchKeyword(string searchKeywordToSet);
		void setCurrentTask(Task currentTaskToSet);

	protected:
		// All Command Attributes
		bool _isParsedCorrectly;
		bool _isCommandValid;
		int _commandTaskIndex;
		string _searchKeyword;
		string _userMessage;
		Task* _currentTask;
		State* _currentState;
		string _logFileName;
		bool _loggingModeOn;

		// All Protected Functions
		bool checkIsParsedCorrectly();
		void retrieveExistingViewState();
		void retrieveExistingCurrentState();
		void setNewCurrentState();
		void setNewViewState();
		void addThisCommandToHistory(Command* commandToAdd);
		void addUserMessageToCurrentState();
		void resetLogicDataSettings();
		void log(string stringToLog);
};

#endif