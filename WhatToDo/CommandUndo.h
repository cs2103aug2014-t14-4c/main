#pragma once
#include "Command.h"
#include "LogicData.h"
using namespace std;

class CommandUndo: public Command {
	public:
		CommandUndo(void);
		void execute();

	private:
		void runAllCommandsAgain();
		void storeRemainingCommandsInHistory(LogicData* myLogicData);
		vector<Command> _commandHistory;
		int _currentCommandHistoryIndex;
		bool checkIsUndoPossible();
};

