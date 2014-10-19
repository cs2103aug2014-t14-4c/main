#include "CommandDone.h"

// These are the static variables that cannot be initialized in header file

string CommandDone::LOGGING_MSG_EXECUTE_COMMAND_DONE = "\nCommand Done Initiated:\n";
string CommandDone::LOGGING_MSG_PERFORM_DONE = "Function called: performDoneOperation(): _commandTaskIndex marked as done: %s\n";


CommandDone::CommandDone(void) {
}

void CommandDone::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_DONE.c_str());
	log(buffer);
	assert(_commandTaskIndex >= 0);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		performDoneOperation();
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

void CommandDone::performDoneOperation() {
	_currentState->doneTask(_commandTaskIndex);
	sprintf_s(buffer, LOGGING_MSG_PERFORM_DONE.c_str(), to_string(_commandTaskIndex).c_str());
	log(buffer);
	return;
}