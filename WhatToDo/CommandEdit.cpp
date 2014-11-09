//****************************************************************************
//@author A0110648L

#include "CommandEdit.h"

CommandEdit::CommandEdit(void) {
}

void CommandEdit::execute() {
	sprintf_s(buffer, MSG_LOGGING_EXECUTE_COMMAND_EDIT.c_str());
	log(buffer);
	
	try {
		checkIsParsedCorrectly();
		assert(_currentTask != NULL);
		assert(_commandTaskIndex >= 0);

		retrieveExistingCurrentState();

		checkIsCommandValid();
		deleteExistingTask();
		performAddOperation();
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

void CommandEdit::deleteExistingTask() {
	_currentState->deleteTask(_commandTaskIndex);

	sprintf_s(buffer, MSG_LOGGING_DELETE_EXISTING_TASK.c_str(), 
		to_string(_commandTaskIndex).c_str());
	log(buffer);
	return;
}

void CommandEdit::performAddOperation() {
	_currentState->addTask(*_currentTask, true, _commandTaskIndex);
	_actionMessage = MSG_ACTION_EDIT;

	sprintf_s(buffer, MSG_LOGGING_PERFORM_ADD.c_str());
	log(buffer);
	return;
}
