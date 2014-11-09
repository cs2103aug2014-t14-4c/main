//****************************************************************************
//@author A0110648L

#include "CommandClear.h"

CommandClear::CommandClear(void) {
}

void CommandClear::execute() {
	sprintf_s(buffer, MSG_LOGGING_EXECUTE_COMMAND_CLEAR.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		retrieveExistingCurrentState();
		resetLastActionType();
		resetUserMessage();
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

void CommandClear::resetLastActionType() {
	_currentState->setLastActionType(State::NONE);
	return;
}

void CommandClear::resetUserMessage() {
	_currentState->setUserMessage(STRING_EMPTY);
	return;
}