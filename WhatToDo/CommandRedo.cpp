#include "CommandRedo.h"


CommandRedo::CommandRedo(void)
{
}

void CommandRedo::execute() {
	if (!_parsedStatus) {
		return;
	}
	_commandHistory = LogicData::getCommandHistory();
	_currentCommandHistoryIndex = LogicData::getCurrentCommandHistoryIndex();
	_isCommandValid = checkIsRedoPossible();
	if (_isCommandValid) {
		LogicData::resetToInitialSettings();
		runAllCommandsAgain();
		storeRemainingCommandsInHistory();
	}
	return;
}

void CommandRedo::runAllCommandsAgain() {
	int i;
	for (i=0; i<_currentCommandHistoryIndex; i++) {
		_commandHistory[i]->execute();
	}
	return;
}

void CommandRedo::storeRemainingCommandsInHistory() {
	int i;
	for (i=_currentCommandHistoryIndex; unsigned(i)<_commandHistory.size(); i++) {
		LogicData::addCommandToHistory(_commandHistory[i]);
	}
	LogicData::setCommandHistoryIndex(_currentCommandHistoryIndex);
	return;
}

bool CommandRedo::checkIsRedoPossible() {
	bool isRedoPossible;
	if (unsigned(_currentCommandHistoryIndex) >= _commandHistory.size()) {
		isRedoPossible = false;
	}
	else {
		isRedoPossible = true;
		_currentCommandHistoryIndex++;
	}
	return isRedoPossible;
}