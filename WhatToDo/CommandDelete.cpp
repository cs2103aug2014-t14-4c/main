#include "CommandDelete.h"

CommandDelete::CommandDelete(void) {
}

void CommandDelete::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_DELETE.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		assert(_commandTaskIndex >= 0);
		retrieveExistingCurrentState();
		performDeleteOperation();
		addThisCommandToHistory(this);
		addActionMessageToCurrentState();
		setNewCurrentState();
		setNewViewState();
	}
	catch (string errorMsg) {
		_userMessage = errorMsg;
		retrieveExistingViewState();
		addUserMessageToCurrentState();
		setNewViewState();
	}
	
	return;
}

void CommandDelete::performDeleteOperation() {
	_currentState->deleteTask(_commandTaskIndex, true);
	_actionMessage = ACTION_MSG_DELETED;
	_currentState->setUserMessage(STRING_EMPTY);

	sprintf_s(buffer, LOGGING_MSG_PERFORM_DELETE.c_str(), 
		to_string(_commandTaskIndex).c_str());
	log(buffer);
	return;
}
