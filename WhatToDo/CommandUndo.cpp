#include "CommandUndo.h"


CommandUndo::CommandUndo(void)
{
}

void CommandUndo::execute() {
	checkIsParsedCorrectly();
	retrieveCommandHistory();
	retrieveCommandHistoryIndex();
	assert(_currentCommandHistoryIndex >= 0);
	assert(_currentCommandHistoryIndex <= _commandHistory.size());
	checkIsCommandValid();

	if (_isParsedCorrectly && _isCommandValid) {
		resetLogicDataSettings();
		runAllRelevantCommandsAgain();
		storeRemainingCommandsInHistory();
	}

	return;
}

void CommandUndo::runAllRelevantCommandsAgain() {
	int i;
	for (i=0; i<_currentCommandHistoryIndex; i++) {
		_commandHistory[i]->execute();
	}
	return;
}

void CommandUndo::storeRemainingCommandsInHistory() {
	int i;
	for (i=_currentCommandHistoryIndex; unsigned(i)<_commandHistory.size(); i++) {
		LogicData::addCommandToHistory(_commandHistory[i]);
	}
	LogicData::setCommandHistoryIndex(_currentCommandHistoryIndex);
	return;
}

bool CommandUndo::checkIsCommandValid() {
	bool isUndoPossible;
	if (_currentCommandHistoryIndex <= 0) {
		isUndoPossible = false;
	}
	else {
		isUndoPossible = true;
		_currentCommandHistoryIndex--;
	}
	return isUndoPossible;
}

void CommandUndo::retrieveCommandHistory() {
	_commandHistory = LogicData::getCommandHistory();
	return;
}

void CommandUndo::retrieveCommandHistoryIndex() {
	_currentCommandHistoryIndex = LogicData::getCurrentCommandHistoryIndex();
	return;
}
