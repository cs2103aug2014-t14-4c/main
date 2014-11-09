//****************************************************************************
//@author A0110648L
//
// This is the parent Command superclass, which contains certain concrete methods 
// that will be used by its children, as well a virtual execute function that
// should be implemented by its concrete children Command classes. This class
// should be used in accordance with the Command Pattern framework.
//
// Amongst its getters and setters, most are made such that details of a command
// can be altered when a command subclass is created. These details include
// (but are not limited to) the task index, the task itself, the search keyword,
// and the user message.
//
// Apart from these public methods, it contains protected functions that its
// children may inherit that implement functions that perform required interactions
// with LogicData such as (but are not limited to) retrieving and setting 
// LogicData's view or current states, and adding a task to the LogicData's
// command history.
//
// Logging: Amongst its protected functions includes a function that allows for
// easy logging amongst its child classes, which may be turned on and off through
// the initialization logging mode parameter.
//
//****************************************************************************

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

const int INITIAL_VALUE_COMMAND_TASK_INDEX = 0;
const bool INITIAL_VALUE_IS_PARSED_CORRECTLY = true;
const bool INITIAL_VALUE_IS_COMMAND_VALID = true;
const bool INITIAL_VALUE_IS_DONE_STATUS = false;
const bool INITIAL_VALUE_LOGGING_MODE_ON = false;
const string INITIAL_VALUE_SEARCH_KEYWORD = "";
const string INITIAL_VALUE_USER_MESSAGE = "";
const string INITIAL_VALUE_ACTION_MESSAGE = "";
const string INITIAL_VALUE_LOG_FILE_NAME = "CommandLog.txt";

const string STRING_EMPTY = "";

const string MSG_LOGGING_CHECK_IS_PARSED_CORRECTLY = 
	"Function called: checkIsParsedCorrectly(): _userMessage set as:"
	"%s\n";
const string MSG_LOGGING_RETRIEVE_EXISTING_VIEW_STATE = 
	"Function called: retrieveExistingViewState()\n";
const string MSG_LOGGING_RETRIEVE_EXISTING_CURRENT_STATE = 
	"Function called: retrieveExistingCurrentState()\n";
const string MSG_LOGGING_SET_NEW_CURRENT_STATE = 
	"Function called: setNewCurrentState()\n";
const string MSG_LOGGING_SET_NEW_VIEW_STATE = 
	"Function called: setNewViewState()\n";
const string MSG_LOGGING_ADD_THIS_COMMAND_TO_HISTORY = 
	"Function called: addThisCommandToHistory()\n";
const string MSG_LOGGING_ADD_USER_MESSAGE_TO_CURRENT_STATE = 
	"Function called: addUserMessageToCurrentState(): _userMessage wr"
	"itten: %s\n";
const string MSG_LOGGING_RESET_LOGIC_DATA_SETTINGS = 
	"Function called: resetLogicDataSettings()\n";

const string MSG_ERROR_NOT_PARSED_CORRECTLY = 
	"Cannot perform command";


class Command {
	public:
		Command(void);
		virtual void execute();

		// All Getter Functions

		int getTaskIndex();
		bool getParsedStatus();
		string getSearchKeyword();
		string getUserMessage();
		Task getCurrentTask();
		bool getIsDoneStatus();
		int getDoneFilter(void);
		int getTypeFilter(void);
		date getStartDateFilter(void);
		date getEndDateFilter(void);

		// All Setter Functions

		void setTaskIndex(int commandTaskIndexToSet);
		void setParsedStatus(bool parsedStatus);
		void setSearchKeyword(string searchKeywordToSet);
		void setUserMessage(string userMessageToSet);
		void setCurrentTask(Task currentTaskToSet);
		void setIsDoneStatus(bool isDoneStatusToSet);
		void setDoneFilter(int doneFilter);
		void setTypeFilter(int typeFilter);
		void setStartDateFilter(date startDateFilter);
		void setEndDateFilter(date endDateFilter);

	protected:

		// Attributes For Execution

		bool _isParsedCorrectly;
		bool _isCommandValid;
		int _commandTaskIndex;
		string _searchKeyword;
		bool _isDoneStatusToSet;
		string _userMessage;
		string _actionMessage;
		Task* _currentTask;
		State* _currentState;
		int _doneFilter;
		int _typeFilter;
		date _startDateFilter;
		date _endDateFilter;
		char buffer[255];

		// Attributes For Logging

		string _logFileName;
		bool _loggingModeOn;

		// Functions For Execution

		bool checkIsParsedCorrectly();

		// The following functions implement interactions with
		// LogicData by calling LogicData's APIs to obtain existing
		// data for the execution of various commands. The function
		// names ought to be self-explanatory.

		void retrieveExistingViewState();
		void retrieveExistingCurrentState();
		void setNewCurrentState();
		void setNewViewState();
		void addThisCommandToHistory(Command* commandToAdd);
		void addUserMessageToCurrentState();
		void addActionMessageToCurrentState();
		void resetLogicDataSettings();

		// Function For Logging

		void log(string stringToLog);
};

#endif