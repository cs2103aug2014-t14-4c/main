#include "CommandUndo.h"


CommandUndo::CommandUndo(void)
{
}

void CommandUndo::execute() {
	LogicData myLogicData;
	_commandHistory = myLogicData.getCommandHistory();
	_currentCommandHistoryIndex = myLogicData.getCurrentCommandHistoryIndex() - 1;
	_isCommandValid = checkIsUndoPossible();
	if (_isCommandValid) {
		myLogicData.resetToInitialSettings();
		runAllCommandsAgain();
		storeRemainingCommandsInHistory(&myLogicData);
	}
	return;
}

void CommandUndo::runAllCommandsAgain() {
	int i;
	for (i=0; i<=_currentCommandHistoryIndex; i++) {
		_commandHistory[i].execute();
	}
	return;
}

void CommandUndo::storeRemainingCommandsInHistory(LogicData* myLogicData) {
	int i;
	for (i=_currentCommandHistoryIndex+1; unsigned(i)<_commandHistory.size(); i++) {
		myLogicData->addCommandToHistory(_commandHistory[i]);
	}
	return;
}

bool CommandUndo::checkIsUndoPossible() {
	bool isUndoPossible;
	if (_currentCommandHistoryIndex <= 0) {
		isUndoPossible = false;
		_userMessage = "There are no commands left to undo!";
	}
	else {
		isUndoPossible = true;
		_currentCommandHistoryIndex--;
	}
	return isUndoPossible;
}