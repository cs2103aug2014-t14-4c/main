#include "CommandUndo.h"


CommandUndo::CommandUndo(void)
{
}

void CommandUndo::execute() {
	if (!_parsedStatus) {
		return;
	}
	_commandHistory = LogicData::getCommandHistory();
	_currentCommandHistoryIndex = LogicData::getCurrentCommandHistoryIndex();
	_isCommandValid = checkIsUndoPossible();
	if (_isCommandValid) {
		LogicData::resetToInitialSettings();
		runAllCommandsAgain();
		storeRemainingCommandsInHistory();
	}
	return;
}

void CommandUndo::runAllCommandsAgain() {
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

bool CommandUndo::checkIsUndoPossible() {
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