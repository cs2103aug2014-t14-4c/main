#include "CommandRedo.h"


CommandRedo::CommandRedo(void)
{
}

void CommandRedo::execute() {
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

bool CommandRedo::checkIsCommandValid() {
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