#include "CommandRedo.h"

// These are the static variables that cannot be initialized in header file

string CommandRedo::LOGGING_MSG_EXECUTE_COMMAND_REDO = "\nCommand Redo Initiated:\n";
string CommandRedo::LOGGING_MSG_CHECK_IS_COMMAND_VALID = "Function called: checkIsCommandValid(): updated _currentCommandHistoryIndex: %s\nFunction called: checkIsCommandValid(): isRedoPossible: %s\n";

string CommandRedo::ERROR_MSG_CANNOT_REDO_ANYMORE = "Cannot redo anymore!";


CommandRedo::CommandRedo(void) {
}

void CommandRedo::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_REDO.c_str());
	log(buffer);
	retrieveCommandHistory();
	retrieveCommandHistoryIndex();
	
	try {
		checkIsParsedCorrectly();
		assert(_currentCommandHistoryIndex >= 0);
		assert(_currentCommandHistoryIndex <= _commandHistory.size());
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
		throw ERROR_MSG_CANNOT_REDO_ANYMORE;
		isRedoPossible = false;
	}
	else {
		isRedoPossible = true;
		_currentCommandHistoryIndex++;
	}

	sprintf_s(buffer, LOGGING_MSG_CHECK_IS_COMMAND_VALID.c_str(), to_string(_currentCommandHistoryIndex).c_str(), to_string(isRedoPossible).c_str());
	log(buffer);
	return isRedoPossible;
}