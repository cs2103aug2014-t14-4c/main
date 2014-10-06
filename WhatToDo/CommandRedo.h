#pragma once
#include "Command.h"
#include "LogicData.h"
using namespace std;

class CommandRedo: public Command {
	public:
		CommandRedo(void);
		void execute();

	private:
		void runAllCommandsAgain();
		void storeRemainingCommandsInHistory();
		vector<Command*> _commandHistory;
		int _currentCommandHistoryIndex;
		bool checkIsRedoPossible();

};

