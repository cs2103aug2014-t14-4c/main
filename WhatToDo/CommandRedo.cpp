#include "CommandRedo.h"


CommandRedo::CommandRedo(void)
{
}

void CommandRedo::execute() {
	log("\nCommand Redo Initiated:\n");
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

	log("Function called: checkIsCommandValid(): updated _currentCommandHistoryIndex: " + to_string(_currentCommandHistoryIndex) + "\n");
	log("Function called: checkIsCommandValid(): isUndoPossible: " + to_string(isRedoPossible) + "\n");
	return isRedoPossible;
}