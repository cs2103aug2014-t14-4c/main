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
		string getUserMessage();
		Task getCurrentTask();
		
		// All Setter Functions

		void setTaskIndex(int commandTaskIndexToSet);
		void setParsedStatus(bool parsedStatus);
		void setSearchKeyword(string searchKeywordToSet);
		void setUserMessage(string userMessageToSet);
		void setCurrentTask(Task currentTaskToSet);

	protected:

		// Command Attributes For Execution

		bool _isParsedCorrectly;
		bool _isCommandValid;
		int _commandTaskIndex;
		string _searchKeyword;
		string _userMessage;
		Task* _currentTask;
		State* _currentState;

		// Command Attributes For Logging

		string _logFileName;
		bool _loggingModeOn;

		// Command Functions For Execution

		bool checkIsParsedCorrectly();
		void retrieveExistingViewState();
		void retrieveExistingCurrentState();
		void setNewCurrentState();
		void setNewViewState();
		void addThisCommandToHistory(Command* commandToAdd);
		void addUserMessageToCurrentState();
		void resetLogicDataSettings();

		// Command Function For Logging

		void log(string stringToLog);

		// All Static Constants And Variables

		static char buffer[255];

		static int INITIAL_VALUE_COMMAND_TASK_INDEX;
		static bool INITIAL_VALUE_IS_PARSED_CORRECTLY;
		static bool INITIAL_VALUE_IS_COMMAND_VALID;
		static bool INITIAL_VALUE_LOGGING_MODE_ON;
		static string INITIAL_VALUE_SEARCH_KEYWORD;
		static string INITIAL_VALUE_USER_MESSAGE;
		static string INITIAL_VALUE_LOG_FILE_NAME;
		static Task* INITIAL_VALUE_CURRENT_TASK;
		static State* INITIAL_VALUE_CURRENT_STATE;

		static string LOGGING_MSG_CHECK_IS_PARSED_CORRECTLY;
		static string LOGGING_MSG_RETRIEVE_EXISTING_VIEW_STATE;
		static string LOGGING_MSG_RETRIEVE_EXISTING_CURRENT_STATE;
		static string LOGGING_MSG_SET_NEW_CURRENT_STATE;
		static string LOGGING_MSG_SET_NEW_VIEW_STATE;
		static string LOGGING_MSG_ADD_THIS_COMMAND_TO_HISTORY;
		static string LOGGING_MSG_ADD_USER_MESSAGE_TO_CURRENT_STATE;
		static string LOGGING_MSG_RESET_LOGIC_DATA_SETTINGS;

		static string ERROR_MSG_NOT_PARSED_CORRECTLY;
};

#endif