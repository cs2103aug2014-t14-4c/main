#include "CommandClear.h"

// These are the static variables that cannot be initialized in header file

string CommandClear::LOGGING_MSG_EXECUTE_COMMAND_CLEAR = "\nCommand Clear Initiated:\n";


CommandClear::CommandClear(void) {
}

void CommandClear::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_CLEAR.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		_currentState->setLastActionType(State::NONE);
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
