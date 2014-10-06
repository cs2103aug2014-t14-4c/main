#pragma once
#include "Command.h"
#include "LogicData.h"
#include <iostream>
using namespace std;

class CommandUndo: public Command {
	public:
		CommandUndo(void);
		void execute();

	private:
		void runAllCommandsAgain();
		void storeRemainingCommandsInHistory();
		vector<Command*> _commandHistory;
		int _currentCommandHistoryIndex;
		bool checkIsUndoPossible();
};

