#pragma once
#include "Command.h"
using namespace std;

class CommandUndo: public Command {
	public:
		CommandUndo(void);
		void execute();

	protected:
		// All Protected Attributes
		int _currentCommandHistoryIndex;
		vector<Command*> _commandHistory;

		// All Protected Functions
		void runAllRelevantCommandsAgain();
		void storeRemainingCommandsInHistory();
		bool checkIsCommandValid();
		void retrieveCommandHistory();
		void retrieveCommandHistoryIndex();
};

