#include "CommandDelete.h"

// These are the static variables that cannot be initialized in header file

string CommandDelete::LOGGING_MSG_EXECUTE_COMMAND_DELETE = "\nCommand Delete Initiated:\n";
string CommandDelete::LOGGING_MSG_PERFORM_DELETE = "Function called: performDeleteOperation(): _commandTaskIndex deleted: %s\n";


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
	_currentState->deleteTask(_commandTaskIndex);
	sprintf_s(buffer, LOGGING_MSG_PERFORM_DELETE.c_str(), to_string(_commandTaskIndex).c_str());
	log(buffer);
	return;
}