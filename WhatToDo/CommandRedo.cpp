#include "CommandRedo.h"


CommandRedo::CommandRedo(void)
{
}

void CommandRedo::execute() {
	checkIsParsedCorrectly();
	retrieveCommandHistory();
	retrieveCommandHistoryIndex();
	checkIsCommandValid();

	if (_isParsedCorrectly && _isCommandValid) {
		resetLogicDataSettings();
		runAllRelevantCommandsAgain();
		storeRemainingCommandsInHistory();
	}

	addUserMessageToCurrentState();
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