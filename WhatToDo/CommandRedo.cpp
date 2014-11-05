#include "CommandRedo.h"

CommandRedo::CommandRedo(void) {
}

void CommandRedo::execute() {
	sprintf_s(buffer, MSG_LOGGING_EXECUTE_COMMAND_REDO.c_str());
	log(buffer);
	retrieveCommandHistory();
	retrieveCommandHistoryIndex();
	
	try {
		checkIsParsedCorrectly();
		assert(_currentCommandHistoryIndex >= 0);
		assert(_currentCommandHistoryIndex <= 
			_commandHistory.size());
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
	if ((_currentCommandHistoryIndex < 0) 
			|| (_currentCommandHistoryIndex >= 
			_commandHistory.size())) {
		throw MSG_ERROR_CANNOT_REDO_ANYMORE;
		isRedoPossible = false;
	}
	else {
		isRedoPossible = true;
		_currentCommandHistoryIndex++;
	}

	sprintf_s(buffer, MSG_LOGGING_CHECK_IS_COMMAND_VALID.c_str(), 
		to_string(_currentCommandHistoryIndex).c_str(), 
		to_string(isRedoPossible).c_str());
	log(buffer);
	return isRedoPossible;
}