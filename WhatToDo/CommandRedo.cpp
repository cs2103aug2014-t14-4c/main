#include "CommandRedo.h"


CommandRedo::CommandRedo(void)
{
}

void CommandRedo::execute() {
	LogicData myLogicData;
	_commandHistory = myLogicData.getCommandHistory();
	_currentCommandHistoryIndex = myLogicData.getCurrentCommandHistoryIndex();
	_isCommandValid = checkIsRedoPossible();
	if (_isCommandValid) {
		myLogicData.resetToInitialSettings();
		runAllCommandsAgain();
		storeRemainingCommandsInHistory(&myLogicData);
	}
	return;
}

void CommandRedo::runAllCommandsAgain() {
	int i;
	for (i=0; i<=_currentCommandHistoryIndex; i++) {
		_commandHistory[i].execute();
	}
	return;
}

void CommandRedo::storeRemainingCommandsInHistory(LogicData* myLogicData) {
	int i;
	for (i=_currentCommandHistoryIndex+1; unsigned(i)<_commandHistory.size(); i++) {
		myLogicData->addCommandToHistory(_commandHistory[i]);
	}
	return;
}

bool CommandRedo::checkIsRedoPossible() {
	bool isRedoPossible;
	if (unsigned(_currentCommandHistoryIndex) >= _commandHistory.size() - 1) {
		isRedoPossible = false;
		_userMessage = "There are no commands left to redo!";
	}
	else {
		isRedoPossible = true;
		_currentCommandHistoryIndex++;
	}
	return isRedoPossible;
}