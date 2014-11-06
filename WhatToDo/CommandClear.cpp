#include "CommandClear.h"

CommandClear::CommandClear(void) {
}

void CommandClear::execute() {
	sprintf_s(buffer, MSG_LOGGING_EXECUTE_COMMAND_CLEAR.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		_currentState->setLastActionType(State::NONE);
		_currentState->setUserMessage(STRING_EMPTY);
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
