//****************************************************************************
//@author A0110648L

#include "CommandDone.h"

CommandDone::CommandDone(void) {
}

void CommandDone::execute() {
	sprintf_s(buffer, LOGGING_MSG_EXECUTE_COMMAND_DONE.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		assert(_commandTaskIndex >= 0);

		retrieveExistingCurrentState();

		performDoneOperation();
		addThisCommandToHistory(this);

		addUserMessageToCurrentState();
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

void CommandDone::performDoneOperation() {
	_currentState->doneTask(_commandTaskIndex, _isDoneStatusToSet);

	if (_isDoneStatusToSet) {
		_actionMessage = ACTION_MSG_DONE;
	}
	else {
		_actionMessage = ACTION_MSG_UNDONE;
	}

	_userMessage = STRING_EMPTY;

	sprintf_s(buffer, LOGGING_MSG_PERFORM_DONE.c_str(), 
		to_string(_commandTaskIndex).c_str());
	log(buffer);
	return;
}