#include "CommandRedo.h"


CommandRedo::CommandRedo(void)
{
}

void CommandRedo::execute() {
	log("\nCommand Redo Initiated:\n");
	retrieveCommandHistory();
	retrieveCommandHistoryIndex();
	assert(_currentCommandHistoryIndex >= 0);
	assert(_currentCommandHistoryIndex <= _commandHistory.size());
	
	try {
		checkIsParsedCorrectly();
		checkIsCommandValid();
		resetLogicDataSettings();
		runAllRelevantCommandsAgain();
		storeRemainingCommandsInHistory();
	}
	catch (string errorMsg) {
		_userMessage = errorMsg;
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}

	return;
}

bool CommandRedo::checkIsCommandValid() {
	bool isRedoPossible;
	if ((_currentCommandHistoryIndex < 0) || (_currentCommandHistoryIndex >= _commandHistory.size())) {
		throw string("Cannot redo anymore!");
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