#pragma once

#include "Command.h"

using namespace std;

class CommandUndo: public Command {
	public:
		CommandUndo(void);
		void execute();

	protected:

		// CommandUndo Attributes For Execution

		int _currentCommandHistoryIndex;
		vector<Command*> _commandHistory;
		
		// CommandUndo Functions For Execution

		bool checkIsCommandValid();
		void runAllRelevantCommandsAgain();
		void storeRemainingCommandsInHistory();
		void retrieveCommandHistory();
		void retrieveCommandHistoryIndex();

		// All Static Constants And Variables

		static string LOGGING_MSG_EXECUTE_COMMAND_UNDO;
		static string LOGGING_MSG_RUN_RELEVANT_COMMANDS_AGAIN;
		static string LOGGING_MSG_STORE_REMAINING_COMMANDS;
		static string LOGGING_MSG_CHECK_IS_COMMAND_VALID;
		static string LOGGING_MSG_RETRIEVE_COMMAND_HISTORY;
		static string LOGGING_MSG_RETRIEVE_COMMAND_HISTORY_INDEX;

		static string ERROR_MSG_CANNOT_UNDO_ANYMORE;

};

